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
	std::vector<Entity*> GetOccupants();
	std::vector<Entity*> GetOccupants(Noun type);
	std::vector<Entity*> GetOccupants(Property p, Ruleset* rules);

	void PlaceEntity(Entity* e);
	void RemoveEntity(Entity* entityToRemove);

	// If there are any entities that are STOP that can't be PUSHed out of the way, returns false.
	// If there aren't any solid entities (ones with STOP or PUSH), returns true.
	// If the only solid entities present are PUSHable, they could be pushed out of the way.
	// This tile lacks the information needed to know that, so it does not return a value.
	std::optional<bool> CanBePassedThrough(Ruleset* rules);

	// Returns whether or not this tile has at least 1 entity that is YOU and 1 that is WIN occupying it.
	bool CheckWinCondition(Ruleset* rules);

private:
	std::vector<Entity*> occupants;
};

