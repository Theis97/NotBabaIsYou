#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <optional>

#include "Tile.h"
#include "Entity.h"
#include "Ruleset.h"
#include "InitialEntityDetails.h"

class Level {
public:
	Level(int width, int height, std::vector<InitialEntityDetails> entityDetails);

	// Attempts to move each entitiy in entities (all assumed to be from the same tile) 
	// in the direction given by moveDirection.
	bool TryMoveFromSingleTile(std::vector<Entity*> entities, Direction moveDirection);
	void UpdateRules();
	void TransformEntities(Noun oldType, std::vector<Noun> newTypes);

	bool ProcessPlayerMove(Direction youMoveDirection);

private:
	bool isWon;
	std::vector<Entity> allEntities;
	std::vector<std::vector<Tile>> board;
	Ruleset rules;
};