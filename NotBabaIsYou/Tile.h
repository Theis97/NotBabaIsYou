#pragma once
#include <vector>
#include <map>
#include <optional>

#include "Entity.h"
#include "Property.h"
#include "Ruleset.h"
#include "TextType.h"
#include "InitialEntityDetails.h"

class Tile {
public:
	void PlaceEntity(Entity* e);
	void RemoveEntity(Entity* entityToRemove);

	// Checks if this tile has at least 1 entity with the YOU property
	// and at least 1 entity with the WIN property
	bool CheckWinCondition(Ruleset* rules);

	// Returns true if this tile contains no solid entities (entiies that have the STOP property).
	// Returns false if there are solid entities on this tile.
	// Does not return a value if there are entities with the PUSH property present but
	// there are no solid entities present. The next tile must be polled to check if
	// there is space to push the pushable entities from this tile.
	std::optional<bool> CanPassThrough(Ruleset* rules);

	// Returns a vector of every entities on this tile
	std::vector<Entity*> GetEntities();
	// Returns a vector of all entities of that type on this tile
	std::vector<Entity*> GetEntities(Noun type);
	// Returns a vector of all entities with property p on this tile
	std::vector<Entity*> GetEntities(Property p, Ruleset* rules);

private:
	std::vector<Entity*> occupants;
};

