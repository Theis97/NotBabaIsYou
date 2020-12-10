#include "Ruleset.h"

Ruleset::Ruleset() {
	AddPropertyRule(Noun::text, Property::push);
}

void Ruleset::Reset() {
	nounsToProperties.clear();
	propertiesToNouns.clear();
	transformationRules.clear();
	
	AddPropertyRule(Noun::text, Property::push);
}

void Ruleset::ParseRule(std::vector<Entity*> textEntities) {
	// NOUN IS NOUN & NOUN IS PROPERTY are currently the only valid rule forms
	int segmentCounter = 0;
	Noun nounToApplyTo;
	for (auto &text : textEntities) {
		segmentCounter++;
		TextType currTextType = text->GetTextType().value();
		switch (segmentCounter) {
		case 1:
			if (currTextType == TextType::noun) {
				nounToApplyTo = text->GetNoun().value();
			}
			else {
				segmentCounter = 0;
			}
			break;
		case 2:
			if (!(currTextType == TextType::is)) {
				segmentCounter = 0;
			}
			break;
		case 3:
			if (currTextType == TextType::noun) {
				Noun transformTarget = text->GetNoun().value();
				AddTransformationRule(nounToApplyTo, transformTarget);
				nounToApplyTo = transformTarget;
				segmentCounter = 1;
			}
			else if (currTextType == TextType::property) {
				AddPropertyRule(nounToApplyTo, text->GetReferredProperty().value());
				segmentCounter = 0;
			}
			else {
				segmentCounter = 0;
			}
			break;
		default:
			// something is wrong here
			break;
		}
	}
}

bool Ruleset::IsEntityProperty(Noun type, Property p) {
	std::set<Property> properties = nounsToProperties[type];
	return properties.find(p) != properties.end();
}

std::set<Noun> Ruleset::GetEntityTypesWith(Property p) {
	return propertiesToNouns[p];
}

std::map<Noun, std::set<Noun>> Ruleset::GetTransformationRules() {
	return transformationRules;
}

std::map<Noun, std::set<Property>> Ruleset::GetRulesByNoun() {
	return nounsToProperties;
}

void Ruleset::SetRule(Noun n, Property p) {
	AddPropertyRule(n, p);
}


void Ruleset::AddPropertyRule(Noun n, Property p) {
	std::set<Property> properties = nounsToProperties[n];
	properties.insert(p);
	nounsToProperties[n] = properties;

	std::set<Noun> nouns = propertiesToNouns[p];
	nouns.insert(n);
	propertiesToNouns[p] = nouns;
}

void Ruleset::AddTransformationRule(Noun oldType, Noun newType) {
	std::set<Noun> transformTypes = transformationRules[oldType];
	transformTypes.insert(newType);
	transformationRules[oldType] = transformTypes;
}
