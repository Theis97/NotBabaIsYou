#include "pch.h"
#include "../NotBabaIsYou/Level.h"

// TODO
// This test suite tests the correctness of particular behaviors of the game engine

TEST(BehaviorTest, BabaIsNotYou) {
	// Break the rule BABA IS YOU
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, PushIntoSolidObject) {
	// Make sure you don't move when pushing into a solid object
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, YouIsStopMovement) {
	// make BABA IS YOU; BABA IS STOP while at least two babas are standing on the same tile
	// make sure they move together
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(BehaviorTest, WalkThroughWalls) {
	// Test that you can't walk through walls when WALL IS STOP
	// and that you can walk through walls when wall isn't stop
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}