#include "pch.h"
#include "../NotBabaIsYou/Tile.h"

TEST(TileTest, CanGetEntitiesOfType) {
	Tile t;
	Entity e = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });

	t.PlaceEntity(&e);

	std::vector<Entity*> textEntities = t.GetEntities(Noun::text);
	ASSERT_FALSE(textEntities.empty());
	ASSERT_EQ(&e, textEntities[0]);
}

TEST(TileTest, WinConditionDetected) {
	Tile t;
	Entity baba = Entity(InitialEntityDetails{ Noun::baba, 0, 0 });
	Entity flag = Entity(InitialEntityDetails{ Noun::flag, 0, 0 });

	t.PlaceEntity(&baba);
	t.PlaceEntity(&flag);

	Ruleset rules;
	rules.SetRule(Noun::baba, Property::you);
	rules.SetRule(Noun::flag, Property::win);

	bool winner = t.CheckWinCondition(&rules);
	ASSERT_TRUE(winner);
}