#pragma once
#include <vector>
#include <tuple>
#include <string>
#include <optional>

#include "Tile.h"
#include "Entity.h"
#include "Ruleset.h"

struct InitialEntityDetails {
	Noun initialType;
	int initialX;
	int initialY;
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> prop;
};

class Level {
public:
	Level(int height, int width, std::vector<InitialEntityDetails> entityDetails);

	void UpdateRules();
	void MoveEntity(Entity* entity, int x, int y);
	void TransformEntities(Noun oldType, Noun newType);
	void ProcessPlayerMove(Direction youMoveDirection);

private:
	bool isWon;
	std::vector<std::vector<Tile>> board;
	Ruleset rules;
};