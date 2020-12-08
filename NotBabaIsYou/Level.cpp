#include <algorithm>

#include "Level.h"

Level::Level() {
	// The tests demanded a default constructor.
	isWon = false;
}

Level::Level(int width, int height, std::vector<InitialEntityDetails> entityDetails) {
	isWon = false;

	board.resize(width);
	board.shrink_to_fit();
	for (auto &column : board) {
		for (int i = 0; i < height; i++) {
			column.push_back(Tile());
		}
		column.shrink_to_fit();
	}

	for (const auto &details : entityDetails) {
		allEntities.push_back(std::make_unique<Entity>(details));
		board[details.x][details.y].PlaceEntity(allEntities.back().get());
	}
	
	UpdateRules();
}

bool Level::TryMoveFromSingleTile(std::vector<Entity*> entities, Direction moveDirection) {
	// TODO: verify that entities are actually from the same tile
	// also refactor
	int x = entities[0]->GetXPos();
	int y = entities[0]->GetYPos();
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
	
	unsigned int uX = x;
	unsigned int uY = y;
	if (uX < 0 || uX >= board.size() || uY < 0 || uY >= board[0].size()) {
		return false;
	}

	std::optional<bool> canMove = board[x][y].canPassThrough(&rules);

	if (canMove.has_value()) {
		if (canMove.value()) {
			for (auto& e : entities) {
				e->Move(moveDirection);
				board[x][y].PlaceEntity(e);
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		// We need to make sure that we can push the pushable entities off of the target tile
		std::vector<Entity*> pushables = board[x][y].GetEntities(Property::push, &rules);
		bool moveSucceeded = TryMoveFromSingleTile(pushables, moveDirection);
		if (moveSucceeded) {
			for (auto& e : entities) {
				e->Move(moveDirection);
				board[x][y].PlaceEntity(e);
			}
			return true;
		}
		else {
			return false;
		}
	}

}

int Level::UpdateRules() {
	// TODO: move current body of this function to "InitializeRules"
	// also implement helper functions to check individual rows/columns
	// and smarter rule change seeking strategy
	// further in the future TODO: stop assuming that only 1 text can be found on a single tile

	int textSegmentsTested = 0;
	// Vertical
	for (unsigned int x = 0; x < board.size(); x++) {
		std::vector<Entity*> potentialRule;
		for (unsigned int y = 0; y < board[0].size(); y++) {
			std::vector<Entity*> textOnTile = board[x][y].GetEntities(Noun::text);
			if (!textOnTile.empty()) {
				potentialRule.push_back(textOnTile[0]);
			}
			else {
				if (!potentialRule.empty()) {
					rules.ParseRule(potentialRule);
					potentialRule.clear();
					textSegmentsTested++;
				}
			}
		}
		if (!potentialRule.empty()) {
			rules.ParseRule(potentialRule);
			potentialRule.clear();
			textSegmentsTested++;
		}
	}

	// Horizontal
	for (unsigned int y = 0; y < board[0].size(); y++) {
		std::vector<Entity*> potentialRule;
		for (unsigned int x = 0; x < board.size(); x++) {
			std::vector<Entity*> textOnTile = board[x][y].GetEntities(Noun::text);
			if (!textOnTile.empty()) {
				potentialRule.push_back(textOnTile[0]);
			}
			else {
				if (!potentialRule.empty()) {
					rules.ParseRule(potentialRule);
					potentialRule.clear();
					textSegmentsTested++;
				}
			}
		}
		if (!potentialRule.empty()) {
			rules.ParseRule(potentialRule);
			potentialRule.clear();
			textSegmentsTested++;
		}
	}

	return textSegmentsTested;
}

void Level::TransformEntities(Noun oldType, std::vector<Noun> newTypes) {
	std::vector<InitialEntityDetails> entitiesToCreate;
	for (auto& e : allEntities) {
		if (e->GetType() == oldType) {
			e->Transform(newTypes[0]);
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
		board[details.x][details.y].PlaceEntity(allEntities.back().get());
	}
}

bool Level::ProcessPlayerMove(Direction youMoveDirection) {
	// TODO: split this function up a bit
	std::vector<std::vector<Entity*>> playerControlledEntities;
	for (auto& e : allEntities) {
		if (rules.IsEntityProperty(e->GetType(), Property::you)) {
			// If there are multiple YOU entities standing on the same tile, 
			// they must all be moved at once given the current implementation,
			// where we combine verifying movement legality and actually making
			// the move. This is because it is possible for a YOU entitiy
			// to also be STOP. If we moved one entity at a time from the same location,
			// entities after the first one will not be able to follow
			// TODO: consider separating verifying if a move is possible from
			// actually making the movement.
			bool positionDuplicate = false;
			for (auto &position : playerControlledEntities) {
				if (position[0]->GetXPos() == e->GetXPos() && position[0]->GetYPos() == e->GetYPos()) {
					position.push_back(e.get());
					positionDuplicate = true;
					break;
				}
			}
			if (!positionDuplicate) {
				std::vector<Entity*> v{e.get()};
				playerControlledEntities.push_back(v);
			}
		}
	}

	if (playerControlledEntities.empty()) {
		// The player doesn't control any entities, so the level
		// must be either rewound or restarted
		return false;
	}

	for (auto& youGroup : playerControlledEntities) {
		int oldX = youGroup[0]->GetXPos();
		int oldY = youGroup[0]->GetYPos();
		bool success = TryMoveFromSingleTile(youGroup, youMoveDirection);
		if (success) {
			for (auto &entity : youGroup) {
				board[oldX][oldY].RemoveEntity(entity);
			}
		}
	}

	rules.Reset();
	UpdateRules();

	std::map<Noun, std::set<Noun>> pendingTransformations = rules.GetPendingTransformations();
	for (auto &transformation :  pendingTransformations) {
		Noun oldType = transformation.first;
		std::vector<Noun> newTypes(transformation.second.begin(), transformation.second.end());
		TransformEntities(oldType, newTypes);
	}
	rules.ClearPendingTransformations();

	bool win = false;
	for (unsigned int x = 0; x < board.size(); x++) {
		for (unsigned int y = 0; y < board[0].size(); y++) {
			win = board[x][y].CheckWinCondition(&rules);
		}
	}
	if (win) {
		isWon = true;
	}

	return true;
}

bool Level::GetIsWon() {
	return isWon;
}

std::vector<Entity*> Level::GetAllEntities() {
	std::vector<Entity*> entitiesToObserve;
	for (int i = 0; i < allEntities.size(); i++) {
		entitiesToObserve.push_back(allEntities[i].get());
	}
	return entitiesToObserve;
}
