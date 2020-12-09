#include <iostream>
#include "Tile.h"

void Tile::PlaceEntity(Entity* e) {
	occupants.push_back(e);
}

void Tile::RemoveEntity(Entity* entityToRemove) {
	for (auto it = occupants.begin(); it < occupants.end(); it++) {
		if (*it == entityToRemove) {
			occupants.erase(it);
			break;
		}
	}
}

std::vector<Entity*> Tile::GetEntities() {
	return std::vector<Entity*>(occupants);
}

std::vector<Entity*> Tile::GetEntities(Noun type) {
	std::vector<Entity*> entitiesOfType;
	for (auto &e : occupants) {
		if (e->GetType() == type) {
			entitiesOfType.push_back(e);
		}
	}
	return entitiesOfType;
}

std::vector<Entity*> Tile::GetEntities(Property p, Ruleset* rules) {
	std::vector<Entity*> entitiesWithProperty;
	for (auto& e : occupants) {
		if (rules->IsEntityProperty(e->GetType(), p)) {
			entitiesWithProperty.push_back(e);
		}
	}
	return entitiesWithProperty;
}

std::optional<bool> Tile::canPassThrough(Ruleset* rules) {
	bool pushablePresent = false;
	for (auto& e : occupants) {
		Noun type = e->GetType();
		if (rules->IsEntityProperty(type, Property::stop) && !rules->IsEntityProperty(type, Property::push)) {
			return false;
		}
		if (rules->IsEntityProperty(type, Property::push)) {
			pushablePresent = true;
		}
	}
	if (pushablePresent) {
		return std::nullopt;
	}
	else {
		return true;
	}
}

bool Tile::CheckWinCondition(Ruleset* rules) {
	if (occupants.size() < 1) {
		return false;
	}
	std::vector<Entity*> youEntities = GetEntities(Property::you, rules);
	std::vector<Entity*> winEntities = GetEntities(Property::win, rules);

	return (!youEntities.empty()) && (!winEntities.empty());
}