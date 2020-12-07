#pragma once
#include <optional>

#include "Noun.h"
#include "Direction.h"
#include "Ruleset.h"
#include "TextType.h"
#include "Property.h"

class Ruleset;

class Entity {
public:
	Entity(Noun n, int x, int y);
	Entity(Noun n, int x, int y, TextType t, Noun noun, Property referredProperty);

	void Move(Direction direction);
	void Transform(Noun newType);

	void CheckProperties(Ruleset* rules);

protected:
	int xPos;
	int yPos;
	Noun type;
	Direction orientation;
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> referredProperty;
};