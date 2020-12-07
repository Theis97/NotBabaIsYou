#include "Entity.h"

Entity::Entity(Noun n, int x, int y)
	: type(n), xPos(x), yPos(y), orientation(Direction::down) {}

void Entity::Transform(Noun newType) {
	type = newType;
}

void Entity::Move(Direction direction) {
	// Assume that this will be a valid position
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
