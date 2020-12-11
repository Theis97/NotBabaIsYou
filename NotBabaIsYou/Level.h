#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "Tile.h"
#include "Entity.h"
#include "Ruleset.h"
#include "InitialEntityDetails.h"

class Level {
public:
	Level();
	Level(int width, int height, std::vector<InitialEntityDetails> entityDetails);

	void ProcessTurn(Direction youMoveDirection);

	// Scans the board for potential rules and hands them to the Ruleset
	void UpdateRules();

	// Transforms all entities of oldType into each of the newTypes.
	// If there is more than one newType, new entities are spawned
	// in addition to transforming the original entity.
	// newTypes must contain at least 1 entry.
	void TransformEntities(Noun oldType, std::vector<Noun> newTypes);

	Ruleset* GetRules();
	std::vector<Entity*> GetAllEntities();
	std::vector<Entity*> GetEntitiesAt(int x, int y);
	bool GetIsWon();
	
	// Checks if any entities are currently YOU.
	// Most of the time, if there are no YOU entities, 
	// the level needs to be restarted/rewound.
	bool DoYouExist();

	// Returns whether or not some entity attempting to move to the position x,y can actually
	// move there. Any entities that need to be pushed along the way are also returned.
	std::pair<bool, std::vector<Entity*>> IsMoveToValid(int x, int y, Direction moveDirection);

private:
	int boardWidth;
	int boardHeight;
	int turnCounter;
	bool isWon;
	std::vector<std::vector<Tile>> board;
	Ruleset rules;
	std::vector<std::unique_ptr<Entity>> allEntities;
	std::map<Noun, std::set<Entity*>> entitiesByType;

	// A flag that gets set when any text is moved, 
	// so we know when the rules may need updating.
	bool checkRules;

	// Changes the coordinates x,y to those of the next tile one step in moveDirection
	void UpdateToNextPosition(int& x, int& y, Direction moveDirection);
	void HandleMovement(Direction youMoveDirection);

	// Of the entities passed in, this only returns the ones that should
	// be allowed to move in the directions they are paired with. It also adds in
	// any entities that need to be pushed in order to move in that direction.
	std::vector<std::pair<Entity*, Direction>> 
		ValidateMoves(std::vector<std::pair<Entity*, Direction>> movingEntities);

	// Moves all entities in the directions they are paired with
	// Has absolutely no regard for whether these moves should be allowed.
	void MakeMoves(std::vector<std::pair<Entity*, Direction>> movingEntities);

	void CheckColumnForRules(int column);
	void CheckRowForRules(int row);

	bool CheckForVictory();
};