#include "pch.h"
#include "../NotBabaIsYou/Tile.h"

TEST(TileTest, TestGettingEntitiesOfType) {
	Tile t;
	Entity e = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });

	t.PlaceEntity(&e);

	std::vector<Entity*> textEntities = t.GetEntities(Noun::text);
	ASSERT_FALSE(textEntities.empty());
	ASSERT_EQ(&e, textEntities[0]);
}