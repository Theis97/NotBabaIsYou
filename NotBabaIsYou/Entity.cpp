#include "Entity.h"

Entity::Entity(InitialEntityDetails e) 
	: type(e.type), xPos(e.x), yPos(e.y), lastTransformed(-1), textType(e.textType), 
	noun(e.noun), referredProperty(e.prop), orientation(Direction::down) {}

int Entity::GetXPos() {
	return xPos;
}

int Entity::GetYPos() {
	return yPos;
}

Noun Entity::GetType() {
	return type;
}

int Entity::GetLastTransformed() {
	return lastTransformed;
}

std::optional<TextType> Entity::GetTextType() {
	return textType;
}

std::optional<Noun> Entity::GetNoun() {
	return noun;
}

std::optional<Property> Entity::GetReferredProperty() {
	return referredProperty;
}

void Entity::DoTransformation(Noun newType, int currentTurn) {
	if (newType == Noun::text) {
		textType = TextType::noun;
		noun = type;
	}
	type = newType;
	lastTransformed = currentTurn;
}

void Entity::Move(Direction direction) {
	// Assumes that this will be a valid position
	switch (direction)
	{
	case Direction::up:
		yPos++;
		break;
	case Direction::right:
		xPos++;
		break;
	case Direction::down:
		yPos--;
		break;
	case Direction::left:
		xPos--;
		break;
	default:
		break;
	}
	orientation = direction;
}
