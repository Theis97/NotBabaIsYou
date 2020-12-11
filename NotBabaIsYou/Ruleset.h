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
	
	// Reads each piece of text in the order it is given.
	// Adds any valid rules it parses to the active rules.
	// Currently only accepts rules of these forms:
	// {NOUN} IS {NOUN}
	// {NOUN} IS {PROPERTY}
	void ParseRule(std::vector<Entity*> textEntities);

	// Lookup functions
	bool DoesTypeHaveProperty(Noun type, Property p);
	std::set<Noun> GetEntityTypesWith(Property p);

	std::map<Noun, std::set<Property>> GetPropertyRules();
	std::map<Noun, std::set<Noun>> GetTransformationRules();

private:
	void AddPropertyRule(Noun n, Property p);
	void AddTransformationRule(Noun oldType, Noun newType);

	std::map<Noun, std::set<Property>> nounsToProperties;
	std::map<Property, std::set<Noun>> propertiesToNouns;
	std::map<Noun, std::set<Noun>> transformationRules;
};
