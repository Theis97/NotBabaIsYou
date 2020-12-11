#pragma once

enum class Property {
	you, // Controlled by the player
	stop, // Solid, so it prevents other entities from moving onto its tile
	push, // Solid, but can be pushed out of the way by other entities
	win // If a YOU entity is on the same tile as this, win the level.
};