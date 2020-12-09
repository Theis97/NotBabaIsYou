#include "pch.h"
#include "BabaIsTest.h"
#include "../NotBabaIsYou/Level.h"

// This test suite tests the correctness of particular behaviors of the game engine
class BehaviorTest : public BabaIsTest {};
TEST_F(BehaviorTest, BasicMovement) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });

	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 2, false);
	AddToVector(entities, babaIsYou);

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

TEST_F(BehaviorTest, BasicPush) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;
	
	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 4, false);
	std::vector<InitialEntityDetails> rockIsPush = ConstructRule(Noun::rock, Property::push, 0, 0, false);
	AddToVector(entities, babaIsYou);
	AddToVector(entities, rockIsPush);

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 2, 2 });

	Level lvl = Level(width, height, entities);

	bool didMoveAllegedlySucceed = lvl.ProcessPlayerMove(Direction::right);
	ASSERT_TRUE(didMoveAllegedlySucceed);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 2);
		}
		if (e->GetType() == Noun::rock) {
			ASSERT_EQ(e->GetXPos(), 3);
			ASSERT_EQ(e->GetYPos(), 2);
		}
	}
}

TEST_F(BehaviorTest, WinCheckWorks) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 2, false);
	std::vector<InitialEntityDetails> flagIsWin = ConstructRule(Noun::flag, Property::win, 0, 0, false);
	AddToVector(entities, babaIsYou);
	AddToVector(entities, flagIsWin);

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });
	entities.push_back(InitialEntityDetails{ Noun::flag, 2, 1 });

	Level lvl = Level(width, height, entities);

	bool didMoveAllegedlySucceed = lvl.ProcessPlayerMove(Direction::right);
	ASSERT_TRUE(didMoveAllegedlySucceed);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 1);
		}
		if (e->GetType() == Noun::flag) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 1);
		}
	}

	Ruleset* rules = lvl.GetRules();
	ASSERT_TRUE(rules->IsEntityProperty(Noun::baba, Property::you));
	ASSERT_TRUE(rules->IsEntityProperty(Noun::flag, Property::win));

	ASSERT_TRUE(lvl.GetIsWon());
}

TEST_F(BehaviorTest, DISABLED_PushIntoSolidObject) {
	// Make sure you don't move when pushing into a solid object

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(BehaviorTest, DISABLED_BabaIsNotYou) {
	// Break the rule BABA IS YOU
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(BehaviorTest, DISABLED_YouIsStopMovement) {
	// make BABA IS YOU; BABA IS STOP while at least two babas are standing on the same tile
	// make sure they move together
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(BehaviorTest, DISABLED_WalkThroughWalls) {
	// Test that you can't walk through walls when WALL IS STOP
	// and that you can walk through walls when wall isn't stop
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}