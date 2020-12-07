#pragma once
#include <map>
#include <vector>
#include <set>

#include "Entity.h"
#include "Property.h"

class Entity;

class Ruleset {
public:
	Ruleset();
	void Reset();
	void ParseRule(std::vector<Entity*> textEntities);
	std::vector<Property> GetProperties(Noun type);
	bool EntityIsProperty(Noun type, Property p);

private:
	std::map<Noun, std::set<Property>> rules;
};
