#include "Tile.h"

std::vector<Entity*> Tile::GetOccupants() {
	return std::vector<Entity*>(occupants);
}

std::vector<Entity*> Tile::GetOccupants(Noun type) {
	std::vector<Entity*> entitiesOfType;
	for (auto &e : occupants) {
		if (e->GetType() == type) {
			entitiesOfType.push_back(e);
		}
	}
	return entitiesOfType;
}

std::vector<Entity*> Tile::GetOccupants(Property p, Ruleset* rules) {
	std::vector<Entity*> entitiesWithProperty;
	for (auto& e : occupants) {
		if (rules->DoesTypeHaveProperty(e->GetType(), p)) {
			entitiesWithProperty.push_back(e);
		}
	}
	return entitiesWithProperty;
}

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

std::optional<bool> Tile::CanBePassedThrough(Ruleset* rules) {
	bool pushablePresent = false;
	for (auto& e : occupants) {
		Noun type = e->GetType();
		if (rules->DoesTypeHaveProperty(type, Property::stop) 
			&& !rules->DoesTypeHaveProperty(type, Property::push)) {
			return false;
		}
		if (rules->DoesTypeHaveProperty(type, Property::push)) {
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
	std::vector<Entity*> youEntities = GetOccupants(Property::you, rules);
	std::vector<Entity*> winEntities = GetOccupants(Property::win, rules);
	return !youEntities.empty() && !winEntities.empty();
}