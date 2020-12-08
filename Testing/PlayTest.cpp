#include "pch.h"
#include "PlayTest.h"

// The tests in this test suite are meant to simulate typical gameplay

PlayTest::PlayTest() {
	int width = 33;
	int height = 18;
	std::vector<InitialEntityDetails> entities;

	// Construct Level 0 from Baba Is You
	for (int x = 11; x < 22; x++) {
		entities.push_back(InitialEntityDetails { Noun::wall, x, 9});
		entities.push_back(InitialEntityDetails { Noun::wall, x, 3});
	}

	for (int y = 6; y < 9; y++) {
		entities.push_back(InitialEntityDetails{ Noun::rock, 16, y });
	}

	entities.push_back(InitialEntityDetails{ Noun::baba, 12, 7 });

	entities.push_back(InitialEntityDetails{ Noun::flag, 20, 7 });

	entities.push_back(InitialEntityDetails{ Noun::text, 11, 11, TextType::noun, Noun::baba });
	entities.push_back(InitialEntityDetails{ Noun::text, 12, 11, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 13, 11, TextType::property, std::nullopt, Property::you });

	entities.push_back(InitialEntityDetails{ Noun::text, 19, 11, TextType::noun, Noun::flag });
	entities.push_back(InitialEntityDetails{ Noun::text, 20, 11, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 21, 11, TextType::property, std::nullopt, Property::win });

	entities.push_back(InitialEntityDetails{ Noun::text, 11, 3, TextType::noun, Noun::wall });
	entities.push_back(InitialEntityDetails{ Noun::text, 12, 3, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 13, 3, TextType::property, std::nullopt, Property::stop });

	entities.push_back(InitialEntityDetails{ Noun::text, 19, 3, TextType::noun, Noun::rock });
	entities.push_back(InitialEntityDetails{ Noun::text, 20, 3, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 21, 3, TextType::property, std::nullopt, Property::push });

	levelZero = Level::Level(width, height, entities);
}

// Take 8 steps to the right and land on the flag.
// There's also a rock that gets pushed along the way.
TEST_F(PlayTest, StraightforwardSolution) {
	for (int i = 0; i < 8; i++) {
		levelZero.ProcessPlayerMove(Direction::right);
	}

	EXPECT_TRUE(levelZero.GetIsWon());
}

TEST_F(PlayTest, DISABLED_BabaIsYouBabaIsWin) {
	// Push BABA IS YOU to the right beyond the walls, taking FLAG IS WIN with it near the end
	// take the IS WIN from FLAG IS WIN to form BABA IS WIN vertically
	// left x2, up x4, right x12, up x1, right x5, down x2, up x2, right x1, down x2, right x1, down x1, left x4, up x1, left x1, down x1, right x1, down x1, left x1, down x1, left x1, up x1
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(PlayTest, DISABLED_WallIsFlagIsWin) {
	// Take WALL IS from WALL IS STOP and move it up by FLAG IS WIN
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(PlayTest, DISABLED_FlagIsYouRockIsWin) {
	// Replace BABA in BABA IS YOU with FLAG, then make ROCK IS WIN
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST_F(PlayTest, DISABLED_WallIsBabaWallIsFlag) {
	// Transform Wall into baba and flag simultaneously, while baba is you and flag is win
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}