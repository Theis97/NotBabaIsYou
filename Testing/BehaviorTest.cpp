#include "pch.h"
#include "../NotBabaIsYou/Level.h"

// This test suite tests the correctness of particular behaviors of the game engine

TEST(BehaviorTest, BasicMovement) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });

	entities.push_back(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	entities.push_back(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });

	Level lvl = Level(width, height, entities);

	bool didMoveAllegedlySucceed = lvl.ProcessPlayerMove(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();

	ASSERT_TRUE(didMoveAllegedlySucceed);

	for (auto &e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 1);
		}
	}

}
TEST(BehaviorTest, DISABLED_BabaIsNotYou) {
	// Break the rule BABA IS YOU
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, DISABLED_PushIntoSolidObject) {
	// Make sure you don't move when pushing into a solid object
	
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, DISABLED_YouIsStopMovement) {
	// make BABA IS YOU; BABA IS STOP while at least two babas are standing on the same tile
	// make sure they move together
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, DISABLED_WalkThroughWalls) {
	// Test that you can't walk through walls when WALL IS STOP
	// and that you can walk through walls when wall isn't stop
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}