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

	//std::vector<Property> GetProperties(Noun type);
	//std::vector<Noun> GetEntityTypes(Property p);
	bool IsEntityProperty(Noun type, Property p);

	std::map<Noun, std::set<Noun>> GetPendingTransformations();
	void ClearPendingTransformations();

	std::map<Noun, std::set<Property>> GetNounsToProperties();

	void SetRule(Noun n, Property p);

private:
	void AddPropertyRule(Noun n, Property p);
	void AddTransformation(Noun oldType, Noun newType);

	std::map<Noun, std::set<Property>> nounsToProperties;
	std::map<Property, std::set<Noun>> propertiesToNouns; // This isn't being used at the moment
	std::map<Noun, std::set<Noun>> pendingTransformations;
};
