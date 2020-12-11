#include <algorithm>
#include <iostream>

#include "Level.h"

Level::Level() {
	// The tests demanded a default constructor. 
	isWon = false;
	checkRules = false;
	turnCounter = 0;
	boardWidth = 0;
	boardHeight = 0;
}

Level::Level(int width, int height, std::vector<InitialEntityDetails> entityDetails) {
	boardWidth = width;
	boardHeight = height;
	isWon = false;
	turnCounter = 0;

	board.resize(boardWidth);
	board.shrink_to_fit();
	for (auto &column : board) {
		for (int i = 0; i < boardHeight; i++) {
			column.push_back(Tile());
		}
		column.shrink_to_fit();
	}

	// Create & place all entities
	for (const auto &details : entityDetails) {
		allEntities.push_back(std::make_unique<Entity>(details));
		std::set<Entity*> entitiesWithType = entitiesByType[details.type];
		entitiesWithType.insert(allEntities.back().get());
		entitiesByType[details.type] = entitiesWithType;
		board[details.x][details.y].PlaceEntity(allEntities.back().get());
	}
	
	UpdateRules();
	checkRules = false;
}

void Level::ProcessTurn(Direction youMoveDirection) {

	HandleMovement(youMoveDirection);

	if (checkRules) {
		UpdateRules();
		checkRules = false;
	}

	std::map<Noun, std::set<Noun>> transformations = rules.GetTransformationRules();
	for (auto& transformation : transformations) {
		Noun oldType = transformation.first;
		std::set<Noun> newTypeSet = transformation.second;

		// {sameNoun} IS {sameNoun} prevents transformations
		if (newTypeSet.find(oldType) == newTypeSet.end()) {
			std::vector<Noun> newTypes(transformation.second.begin(), transformation.second.end());
			TransformEntities(oldType, newTypes);
		}
	}

	isWon = CheckForVictory();
	turnCounter++;
}

void Level::UpdateRules() {
	rules.Reset();
	for (int x = 0; x < boardWidth; x++) {
		CheckColumnForRules(x);
	}

	for (int y = boardHeight - 1; y >= 0; y--) {
		CheckRowForRules(y);
	}
}

void Level::TransformEntities(Noun oldType, std::vector<Noun> newTypes) {
	std::vector<InitialEntityDetails> entitiesToCreate;

	std::set<Entity*> entitiesToTransform = entitiesByType[oldType];
	for (auto& e : entitiesToTransform) {
		if (e->GetLastTransformed() != turnCounter) {
			e->DoTransformation(newTypes[0], turnCounter);

			std::set<Entity*> entitiesOfOldType = entitiesByType[oldType];
			entitiesOfOldType.erase(e);
			entitiesByType[oldType] = entitiesOfOldType;

			std::set<Entity*> entitiesOfNewType = entitiesByType[newTypes[0]];
			entitiesOfNewType.insert(e);
			entitiesByType[newTypes[0]] = entitiesOfNewType;
		}
		// Simultaneous transformations spawn new entities
		for (unsigned int i = 1; i < newTypes.size(); i++) {
			InitialEntityDetails newEntityDetails;
			newEntityDetails.type = newTypes[i];
			newEntityDetails.x = e->GetXPos();
			newEntityDetails.y = e->GetYPos();
			if (newTypes[i] == Noun::text) {
				newEntityDetails.textType = TextType::noun;
				newEntityDetails.noun = oldType;
			}
			entitiesToCreate.push_back(newEntityDetails);
		}
	}

	for (auto& details : entitiesToCreate) {
		allEntities.push_back(std::make_unique<Entity>(details));
		std::set<Entity*> entitiesWithType = entitiesByType[details.type];
		entitiesWithType.insert(allEntities.back().get());
		entitiesByType[details.type] = entitiesWithType;
		board[details.x][details.y].PlaceEntity(allEntities.back().get());
	}
}

Ruleset* Level::GetRules() {
	return &rules;
}

std::vector<Entity*> Level::GetAllEntities() {
	std::vector<Entity*> entitiesToObserve;
	for (unsigned int i = 0; i < allEntities.size(); i++) {
		entitiesToObserve.push_back(allEntities[i].get());
	}
	return entitiesToObserve;
}

std::vector<Entity*> Level::GetEntitiesAt(int x, int y) {
	return board[x][y].GetOccupants();
}

bool Level::GetIsWon() {
	return isWon;
}

bool Level::DoYouExist() {
	std::set<Noun> youTypes = rules.GetEntityTypesWith(Property::you);
	if (youTypes.empty()) {
		return false;
	}

	// There could be a rule saying an entity type is YOU, but no entities of that type
	// actually exist in the level, so we have to check.
	for (auto &type : youTypes) {
		if (!entitiesByType[type].empty()) {
			return true;
		}
	}
	return false;
}

std::pair<bool, std::vector<Entity*>> Level::IsMoveToValid(int x, int y, Direction moveDirection) {
	if (x < 0 || x >= boardWidth || y < 0 || y >= boardHeight) {
		return std::pair(false, std::vector<Entity*>{});
	}

	std::optional<bool> isOpen = board[x][y].CanBePassedThrough(&rules);

	if (isOpen.has_value()) {
		if (isOpen.value()) {
			return std::pair(true, std::vector<Entity*>{});
		}
		else {
			return std::pair(false, std::vector<Entity*>{});
		}
	}
	else {
		// There are PUSHable entities in our way, but we might be able to move them
		// as long as they aren't backed up against a solid entity or the edge of the board
		std::vector<Entity*> pushables = board[x][y].GetOccupants(Property::push, &rules);
		UpdateToNextPosition(x, y, moveDirection);
		std::pair<bool, std::vector<Entity*>> p = IsMoveToValid(x, y, moveDirection);
		bool pushablesCanMove = p.first;

		if (pushablesCanMove) {
			std::vector<Entity*> morePushables = p.second;
			pushables.insert(pushables.end(), morePushables.begin(), morePushables.end());
			return std::pair(true, pushables);
		}
		else {
			return std::pair(false, std::vector<Entity*>{});
		}
	}
}

void Level::UpdateToNextPosition(int& x, int& y, Direction moveDirection) {
	switch (moveDirection) {
	case Direction::up:
		y++;
		break;
	case Direction::right:
		x++;
		break;
	case Direction::down:
		y--;
		break;
	case Direction::left:
		x--;
		break;
	default:
		break;
	}
}

void Level::HandleMovement(Direction youMoveDirection) {
	std::vector<std::pair<Entity*, Direction>> playerEntityMoves;
	std::set<Noun> youTypes = rules.GetEntityTypesWith(Property::you);
	for (auto& type : youTypes) {
		for (auto& e : entitiesByType[type]) {
			playerEntityMoves.push_back(std::pair(e, youMoveDirection));
		}
	}

	std::vector<std::pair<Entity*, Direction>> entitiesToMove = ValidateMoves(playerEntityMoves);
	MakeMoves(entitiesToMove);
}

// This function only returns valid moves from movingEntities and any additional moves that have to be made to allow them.
std::vector<std::pair<Entity*, Direction>> Level::ValidateMoves(std::vector<std::pair<Entity*, Direction>> movingEntities) {
	std::vector<std::pair<Entity*, Direction>> validatedMoves;
	for (auto &entityMove : movingEntities) {
		Entity* e = entityMove.first;
		Direction moveDirection = entityMove.second;
		int x = e->GetXPos();
		int y = e->GetYPos();
		UpdateToNextPosition(x, y, moveDirection);

		if (x >= 0 && x < boardWidth && y >= 0 && y < boardHeight) {
			std::pair<bool, std::vector<Entity*>> p = IsMoveToValid(x, y, moveDirection);
			bool MoveIsValid = p.first;
			std::vector<Entity*> entitiesPushedAlong = p.second;

			if (MoveIsValid) {
				validatedMoves.push_back(entityMove);
				for (auto &pushable : entitiesPushedAlong) {
					validatedMoves.push_back(std::pair(pushable, moveDirection));
				}
			}
		}
	}
	return validatedMoves;
}

// Does absolutely no checks to make sure these moves are valid.
// Use ValidateMoves before using this function.
void Level::MakeMoves(std::vector<std::pair<Entity*, Direction>> movingEntities) {
	for (auto &entityMove : movingEntities) {
		Entity* e = entityMove.first;
		Direction moveDirection = entityMove.second;
		int x = e->GetXPos();
		int y = e->GetYPos();

		board[x][y].RemoveEntity(e);
		UpdateToNextPosition(x, y, moveDirection);
		e->Move(moveDirection);
		board[x][y].PlaceEntity(e);

		// Text moving could mean that a rule was either broken or formed
		if (e->GetType() == Noun::text) {
			checkRules = true;
		}
	}
}

void Level::CheckColumnForRules(int column) {
	std::vector<Entity*> potentialRules;
	for (int y = boardHeight - 1; y >= 0; y--) {
		std::vector<Entity*> textOnTile = board[column][y].GetOccupants(Noun::text);
		if (!textOnTile.empty()) {
			potentialRules.push_back(textOnTile[0]);
		}
		else {
			if (!potentialRules.empty()) {
				rules.ParseRule(potentialRules);
				potentialRules.clear();
			}
		}
	}
	if (!potentialRules.empty()) {
		rules.ParseRule(potentialRules);
		potentialRules.clear();
	}
}

void Level::CheckRowForRules(int row) {
	std::vector<Entity*> potentialRules;
	for (int x = 0; x < boardWidth; x++) {
		std::vector<Entity*> textOnTile = board[x][row].GetOccupants(Noun::text);
		if (!textOnTile.empty()) {
			potentialRules.push_back(textOnTile[0]);
		}
		else {
			if (!potentialRules.empty()) {
				rules.ParseRule(potentialRules);
				potentialRules.clear();
			}
		}
	}
	if (!potentialRules.empty()) {
		rules.ParseRule(potentialRules);
		potentialRules.clear();

	}
}

bool Level::CheckForVictory() {
	std::set<Noun> winTypes = rules.GetEntityTypesWith(Property::win);
	for (auto &type : winTypes) {
		for (auto& winEntity : entitiesByType[type]) {
			if (board[winEntity->GetXPos()][winEntity->GetYPos()].CheckWinCondition(&rules)) {
				return true;
			}
		}
	}
	return false;
}
