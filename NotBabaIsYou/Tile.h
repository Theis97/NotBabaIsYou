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

	bool CheckWinCondition(Ruleset* rules);

	// A tile that doesn't have a STOP entity but does have a PUSH entity on it 
	// cannot tell if an entity can pass through it on its own. The surrounding
	// tiles must be polled for open space to push the entity into.
	std::optional<bool> canPassThrough(Ruleset* rules);

	std::vector<Entity*> GetEntities();
	std::vector<Entity*> GetEntities(Noun type);
	std::vector<Entity*> GetEntities(Property p, Ruleset* rules);

private:
	std::vector<Entity*> occupants;
};

