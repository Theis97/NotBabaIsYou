#include "pch.h"
#include "../NotBabaIsYou/Level.h"


// before all tests -> set up first level of Baba Is You

// This test suite simulates various methods of solving level 0 of Baba Is You
TEST(PlayTest, StraightforwardSolution) {

	// Take 8 steps to the right
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, BabaIsYouBabaIsWin) {
	// Push BABA IS YOU to the right beyond the walls, taking FLAG IS WIN with it near the end
	// take the IS WIN from FLAG IS WIN to form BABA IS WIN vertically
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, WallIsFlagIsWin) {
	// Take WALL IS from WALL IS STOP and move it up by FLAG IS WIN
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, FlagIsYouRockIsWin) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}