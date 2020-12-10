#pragma once
#include <optional>
#include <string>

#include "Noun.h"
#include "Direction.h"
#include "Ruleset.h"
#include "TextType.h"
#include "Property.h"
#include "InitialEntityDetails.h"

class Ruleset;

class Entity {
public:
	Entity(InitialEntityDetails e);

	int GetXPos();
	int GetYPos();
	Noun GetType();
	int GetLastTransformation();
	std::optional<TextType> GetTextType();
	std::optional<Noun> GetNoun();
	std::optional<Property> GetReferredProperty();

	void Move(Direction direction);
	void Transform(Noun newType, int currentTurn);

protected:
	Noun type;
	int xPos;
	int yPos;
	int lastTransformation;
	Direction orientation;

	// All entities of type "text" are expected to have a TextType.
	std::optional<TextType> textType;
	// All entities with a TextType of "noun" are expected to hold the noun they refer to
	std::optional<Noun> noun;
	// All entities with a TexType of "property" are expected to hold the property they refer to
	std::optional<Property> referredProperty;
};