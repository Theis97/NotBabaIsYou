#pragma once
#include <vector>
#include <map>
#include <optional>

#include "Entity.h"
#include "Property.h"
#include "Ruleset.h"
#include "TextType.h"


class Tile {
public:
	void LinkNeighbor(Tile* neighbor, Direction direction);

	bool AttemptEntry(std::vector<Entity*> entities, Direction entryDirection);

	void CreateEntityHere(Noun type);
	void CreateEntityHere(Noun type, std::optional<TextType> t, std::optional<Noun> noun, std::optional<Property> referredProperty);
	void DestroyEntity(Entity* e);
	void RemoveEntity(Entity* e);

	std::vector<Entity*> GetEntities();
	std::vector<Entity*> GetEntities(Noun type);
	std::vector<Entity*> GetEntities(Property p, Ruleset* r);

private:
	std::vector<Entity*> occupants;
	std::map<Direction, Tile*> neighbors;
};

