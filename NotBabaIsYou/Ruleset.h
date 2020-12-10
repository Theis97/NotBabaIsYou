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

	std::set<Noun> GetEntityTypesWith(Property p);
	bool IsEntityProperty(Noun type, Property p);

	std::map<Noun, std::set<Noun>> GetTransformationRules();

	// Returns a mapping of nouns to the set of properties
	// that currently apply to them.
	std::map<Noun, std::set<Property>> GetRulesByNoun();

	void SetRule(Noun n, Property p); // remove this

private:
	void AddPropertyRule(Noun n, Property p);
	void AddTransformationRule(Noun oldType, Noun newType);

	std::map<Noun, std::set<Property>> nounsToProperties;
	std::map<Property, std::set<Noun>> propertiesToNouns;
	std::map<Noun, std::set<Noun>> transformationRules;
};
