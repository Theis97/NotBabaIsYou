#include "pch.h"
#include "BabaIsTest.h"
#include "../NotBabaIsYou/Tile.h"

class TileTest : public BabaIsTest {};

TEST_F(TileTest, CanGetEntitiesOfType) {
	Tile t;
	Entity e = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });

	t.PlaceEntity(&e);

	std::vector<Entity*> textEntities = t.GetOccupants(Noun::text);
	ASSERT_FALSE(textEntities.empty());
	ASSERT_EQ(&e, textEntities[0]);
}

TEST_F(TileTest, WinConditionDetected) {
	Tile t;
	Ruleset rules;
	Entity baba = Entity(InitialEntityDetails{ Noun::baba, 0, 0 });
	Entity flag = Entity(InitialEntityDetails{ Noun::flag, 0, 0 });

	t.PlaceEntity(&baba);
	t.PlaceEntity(&flag);

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity youText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });

	Entity flagText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::flag });
	Entity winText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::win });
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&youText);

	textChunks.push_back(&flagText);
	textChunks.push_back(&isText);
	textChunks.push_back(&winText);

	rules.ParseRule(textChunks);

	bool winner = t.CheckWinCondition(&rules);
	EXPECT_TRUE(winner);
}

TEST_F(TileTest, SameEntityIsYouAndWin) {
	Tile t;
	Ruleset rules;
	Entity baba = Entity(InitialEntityDetails{ Noun::baba, 0, 0 });

	t.PlaceEntity(&baba);

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity youText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });
	Entity winText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::win });
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&youText);

	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&winText);

	rules.ParseRule(textChunks);

	bool winner = t.CheckWinCondition(&rules);
	EXPECT_TRUE(winner);
}