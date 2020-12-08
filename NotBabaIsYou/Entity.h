#pragma once
#include <optional>

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
	std::optional<TextType> GetTextType();
	std::optional<Noun> GetNoun();
	std::optional<Property> GetReferredProperty();

	void Move(Direction direction);
	void Transform(Noun newType);

protected:
	Noun type;
	int xPos;
	int yPos;
	Direction orientation;
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> referredProperty;
};