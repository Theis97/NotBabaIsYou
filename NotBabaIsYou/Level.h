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

	std::pair<bool, std::vector<Entity*>> IsMoveToValid(int x, int y, Direction moveDirection);

	// Of the entities passed in, this only returns the ones that should
	// be allowed to move in the directions they are paired with. It also adds in
	// any entities that need to be pushed in order to move in that direction.
	std::vector<std::pair<Entity*, Direction>> ValidateMoves(std::vector<std::pair<Entity*, Direction>> movingEntities);
	void MakeMoves(std::vector<std::pair<Entity*, Direction>> movingEntities);
	void HandleMovement(Direction youMoveDirection);

	void CheckColumnForRules(int column);
	void CheckRowForRules(int row);
	void UpdateRules();
	void TransformEntities(Noun oldType, std::vector<Noun> newTypes);

	bool ProcessPlayerMove(Direction youMoveDirection);

	bool CheckForVictory();

	bool GetIsWon();
	std::vector<Entity*> GetAllEntities();
	std::vector<Entity*> GetEntitiesAt(int x, int y);
	Ruleset* GetRules();

private:
	int boardWidth;
	int boardHeight;
	int turnCounter;
	bool isWon;
	std::vector<std::unique_ptr<Entity>> allEntities;
	std::vector<std::vector<Tile>> board;
	Ruleset rules;

	void updateCoordinates(int& x, int& y, Direction moveDirection);
};