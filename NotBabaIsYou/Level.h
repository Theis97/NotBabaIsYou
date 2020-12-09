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

	// Attempts to move each entitiy in entities (all assumed to be from the same tile) 
	// in the direction given by moveDirection.
	bool TryMoveFromSingleTile(std::vector<Entity*> entities, Direction moveDirection);
	void CheckColumnForRules(int column);
	void CheckRowForRules(int row);
	void UpdateRules();
	void TransformEntities(Noun oldType, std::vector<Noun> newTypes);

	bool ProcessPlayerMove(Direction youMoveDirection);

	bool GetIsWon();
	std::vector<Entity*> GetAllEntities();
	std::vector<Entity*> GetEntitiesAt(int x, int y);
	Ruleset* GetRules();

private:
	int turnCounter;
	bool isWon;
	std::vector<std::unique_ptr<Entity>> allEntities;
	std::vector<std::vector<Tile>> board;
	Ruleset rules;
};