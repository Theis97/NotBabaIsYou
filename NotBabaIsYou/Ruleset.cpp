#include "Ruleset.h"

Ruleset::Ruleset() {
	AddPropertyRule(Noun::text, Property::push);
}

void Ruleset::Reset() {
	nounsToProperties.clear();
	propertiesToNouns.clear();
	transformationRules.clear();
	
	// For now, TEXT is always PUSH.
	AddPropertyRule(Noun::text, Property::push);
}

void Ruleset::ParseRule(std::vector<Entity*> textEntities) {
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
				// {nounToApplyTo} IS {transformTarget}
				Noun transformTarget = text->GetNoun().value();
				AddTransformationRule(nounToApplyTo, transformTarget);

				// Rules are allowed to overlap, this could be the start of another
				nounToApplyTo = transformTarget;
				segmentCounter = 1;
			}
			else if (currTextType == TextType::property) {
				// {nounToApplyTo} IS {whatever property this text represents}
				AddPropertyRule(nounToApplyTo, text->GetReferredProperty().value());
				segmentCounter = 0;
			}
			else {
				segmentCounter = 0;
			}
			break;
		default:
			// This really shouldn't happen
			segmentCounter = 0;
			break;
		}
	}
}

bool Ruleset::DoesTypeHaveProperty(Noun type, Property p) {
	std::set<Property> properties = nounsToProperties[type];
	return properties.find(p) != properties.end();
}

std::set<Noun> Ruleset::GetEntityTypesWith(Property p) {
	return propertiesToNouns[p];
}

std::map<Noun, std::set<Property>> Ruleset::GetPropertyRules() {
	return nounsToProperties;
}

std::map<Noun, std::set<Noun>> Ruleset::GetTransformationRules() {
	return transformationRules;
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
