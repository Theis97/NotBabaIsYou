#include "pch.h"
#include "../NotBabaIsYou/Level.h"

//TODO
// The tests in this test suite simulate typical gameplay
// within the first level of Baba Is You

// before all tests -> set up first level of Baba Is You

TEST(PlayTest, StraightforwardSolution) {

	// Take 8 steps to the right
	// lvl.ProcessPlayerMove(Direction::right);
	// in a x8 for loop
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, BabaIsYouBabaIsWin) {
	// Push BABA IS YOU to the right beyond the walls, taking FLAG IS WIN with it near the end
	// take the IS WIN from FLAG IS WIN to form BABA IS WIN vertically
	// left x2, up x4, right x12, up x1, right x5, down x2, up x2, right x1, down x2, right x1, down x1, left x4, up x1, left x1, down x1, right x1, down x1, left x1, down x1, left x1, up x1
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, WallIsFlagIsWin) {
	// Take WALL IS from WALL IS STOP and move it up by FLAG IS WIN
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, FlagIsYouRockIsWin) {
	// Replace BABA in BABA IS YOU with FLAG, then make ROCK IS WIN
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(PlayTest, WallIsBabaWallIsFlag) {
	// Transform Wall into baba and flag simultaneously, while baba is you and flag is win
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}