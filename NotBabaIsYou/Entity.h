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
	int GetLastTransformed();

	std::optional<TextType> GetTextType();
	std::optional<Noun> GetNoun();
	std::optional<Property> GetReferredProperty();

	// Updates the entity's internal record of its
	// position when moved in the given direction. 
	// Does not affect board state.
	void Move(Direction direction);

	void DoTransformation(Noun newType, int currentTurn);

private:
	int xPos;
	int yPos;
	Direction orientation;
	Noun type;

	// Entities can only be transformed once per turn, so we keep track
	int lastTransformed;

	// The following only have meaning for text entities.
	// All text entities are expected to have a TextType.
	std::optional<TextType> textType;
	// All entities with a TextType of "noun" are expected to hold the noun they refer to
	std::optional<Noun> noun;
	// All entities with a TexType of "property" are expected to hold the property they refer to
	std::optional<Property> referredProperty;
};