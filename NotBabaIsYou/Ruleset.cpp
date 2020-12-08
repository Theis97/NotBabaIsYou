#include "Ruleset.h"

Ruleset::Ruleset() {
	AddPropertyRule(Noun::text, Property::push);
}

void Ruleset::Reset() {
	nounsToProperties.clear();
	propertiesToNouns.clear();
	ClearPendingTransformations();
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
				AddTransformation(nounToApplyTo, transformTarget);
				nounToApplyTo = transformTarget;
				segmentCounter = 1;
			}
			else if (currTextType == TextType::property) {
				AddPropertyRule(nounToApplyTo, text->GetReferredProperty().value());
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

std::map<Noun, std::set<Noun>> Ruleset::GetPendingTransformations() {
	return pendingTransformations;
}

void Ruleset::ClearPendingTransformations() {
	pendingTransformations.clear();
}


void Ruleset::AddPropertyRule(Noun n, Property p) {
	std::set<Property> properties = nounsToProperties[n];
	properties.insert(p);

	std::set<Noun> nouns = propertiesToNouns[p];
	nouns.insert(n);
}

void Ruleset::AddTransformation(Noun oldType, Noun newType) {
	std::set<Noun> transformTypes = pendingTransformations[oldType];
	transformTypes.insert(newType);
}
