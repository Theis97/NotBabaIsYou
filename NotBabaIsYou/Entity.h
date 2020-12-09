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
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> referredProperty;
};