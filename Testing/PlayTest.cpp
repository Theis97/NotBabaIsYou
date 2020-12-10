#include "pch.h"
#include "BabaIsTest.h"
#include "PlayTest.h"

// The tests in this test suite are meant to simulate typical gameplay

PlayTest::PlayTest() {
	int width = 33;
	int height = 18;
	std::vector<InitialEntityDetails> entities;

	// Construct Level 0 from Baba Is You
	for (int x = 11; x < 22; x++) {
		entities.push_back(InitialEntityDetails { Noun::wall, x, 9});
		entities.push_back(InitialEntityDetails { Noun::wall, x, 5});
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
	for (int i = 0; i < 7; i++) {
		levelZero.ProcessTurn(Direction::right);
	}

	EXPECT_FALSE(levelZero.GetIsWon());
	levelZero.ProcessTurn(Direction::right);
	EXPECT_TRUE(levelZero.GetIsWon());
}

TEST_F(PlayTest, BabaIsYouBabaIsWin) {
	// Push BABA IS YOU to the right beyond the walls, taking FLAG IS WIN with it near the end
	// take the IS WIN from FLAG IS WIN to form BABA IS WIN vertically

	std::vector<Direction> moveSequence{ Direction::left, Direction::left };
	AppendToVector(moveSequence, FormStraightSequence(4, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(12, Direction::right));
	moveSequence.push_back(Direction::up);
	AppendToVector(moveSequence, FormStraightSequence(6, Direction::right));
	AppendToVector(moveSequence, FormNudgeSequence(2, Direction::down));
	moveSequence.push_back(Direction::left);
	moveSequence.push_back(Direction::down);
	moveSequence.push_back(Direction::right);
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormNudgeSequence(4, Direction::left));
	moveSequence.push_back(Direction::right);
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormStraightSequence(4, Direction::left));

	for (auto &move : moveSequence) {
		levelZero.ProcessTurn(move);
	}

	EXPECT_FALSE(levelZero.GetIsWon());
	levelZero.ProcessTurn(Direction::left);
	EXPECT_TRUE(levelZero.GetIsWon());
}

TEST_F(PlayTest, WallIsFlagIsWin) {
	// Take WALL IS from WALL IS STOP and move it up by FLAG IS WIN

	std::vector<Direction> moveSequence{ Direction::left, Direction::left };
	AppendToVector(moveSequence, FormStraightSequence(5, Direction::down));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::right));
	moveSequence.push_back(Direction::up);
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::left));
	moveSequence.push_back(Direction::down);
	moveSequence.push_back(Direction::left);
	AppendToVector(moveSequence, FormNudgeSequence(9, Direction::up));
	moveSequence.push_back(Direction::left);
	AppendToVector(moveSequence, FormStraightSequence(10, Direction::up));
	AppendToVector(moveSequence, FormNudgeSequence(9, Direction::right));
	moveSequence.push_back(Direction::left);
	moveSequence.push_back(Direction::up);
	AppendToVector(moveSequence, FormStraightSequence(10, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::down));

	for (auto& move : moveSequence) {
		levelZero.ProcessTurn(move);
	}

	EXPECT_FALSE(levelZero.GetIsWon());
	levelZero.ProcessTurn(Direction::down);
	EXPECT_TRUE(levelZero.GetIsWon());

	std::vector<Entity*> entities = levelZero.GetAllEntities();
	for (auto& e : entities) {
		std::cerr << NounToString(e->GetType()) << "(" << e->GetXPos() << ", " << e->GetYPos() << ")";
		if (e->GetTextType().has_value()) {
			std::cerr << ": " << TextTypeToString(e->GetTextType().value());
		}
		if (e->GetNoun().has_value()) {
			std::cerr << " " << NounToString(e->GetNoun().value());
		}
		if (e->GetReferredProperty().has_value()) {
			std::cerr << " " << PropertyToString(e->GetReferredProperty().value());
		}
		std::cerr << "\n";
	}
}

TEST_F(PlayTest, FlagIsYouRockIsWin) {
	// Replace BABA in BABA IS YOU with FLAG, then make ROCK IS WIN

	std::vector<Entity*> v = levelZero.GetEntitiesAt(12,7);
	ASSERT_EQ(v.size(), 1);
	Entity* baba = v[0]; 
	std::cerr << "Baba is at (" << baba->GetXPos() << ", " << baba->GetYPos() << ")\n";

	std::vector<Direction> moveSequence{ Direction::left, Direction::left };
	AppendToVector(moveSequence, FormStraightSequence(4, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(12, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(7, Direction::down));
	AppendToVector(moveSequence, FormStraightSequence(4, Direction::left));
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormStraightSequence(7, Direction::right));
	moveSequence.push_back(Direction::down);
	moveSequence.push_back(Direction::right);
	AppendToVector(moveSequence, FormStraightSequence(8, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(5, Direction::left));
	moveSequence.push_back(Direction::up);
	moveSequence.push_back(Direction::left);
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::left));
	
	int stepCount = 0;
	for (auto& move : moveSequence) {
		stepCount++;
		levelZero.ProcessTurn(move);
		std::cerr << "Baba is at (" << baba->GetXPos() << ", " << baba->GetYPos() << ")\n";
	}

	EXPECT_FALSE(levelZero.GetIsWon());
	levelZero.ProcessTurn(Direction::left);
	std::cerr << "Baba is at (" << baba->GetXPos() << ", " << baba->GetYPos() << ")\n";
	EXPECT_TRUE(levelZero.GetIsWon());

	std::vector<Entity*> entities = levelZero.GetAllEntities();
	for (auto &e : entities) {
		std::cerr << NounToString(e->GetType()) << "(" << e->GetXPos() << ", " << e->GetYPos() << ")";
		if (e->GetTextType().has_value()) {
			std::cerr << ": " << TextTypeToString(e->GetTextType().value());
		}
		if (e->GetNoun().has_value()) {
			std::cerr << " " << NounToString(e->GetNoun().value());
		}
		if (e->GetReferredProperty().has_value()) {
			std::cerr << " " << PropertyToString(e->GetReferredProperty().value());
		}
		std::cerr << "\n";
	}
	
}

TEST_F(PlayTest, WallIsBabaWallIsFlag) {
	// Transform Wall into baba and flag simultaneously, while baba is you and flag is win
	std::vector<Entity*> v = levelZero.GetEntitiesAt(12, 7);
	ASSERT_EQ(v.size(), 1);
	Entity* baba = v[0];
	std::cerr << "Baba is at (" << baba->GetXPos() << ", " << baba->GetYPos() << ")\n";

	std::vector<Direction> moveSequence{ Direction::down };
	AppendToVector(moveSequence, FormStraightSequence(10, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::down));
	AppendToVector(moveSequence, FormStraightSequence(10, Direction::left));
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::left));
	AppendToVector(moveSequence, FormNudgeSequence(10, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::left));
	AppendToVector(moveSequence, FormNudgeSequence(9, Direction::up));
	moveSequence.push_back(Direction::left);
	AppendToVector(moveSequence, FormStraightSequence(10, Direction::up));
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::down));
	AppendToVector(moveSequence, FormStraightSequence(14, Direction::right));
	moveSequence.push_back(Direction::up);
	AppendToVector(moveSequence, FormStraightSequence(7, Direction::left));
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormMultiNudgeSequence(2, 3, Direction::up, Direction::left));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::right));
	AppendToVector(moveSequence, FormStraightSequence(3, Direction::up));
	moveSequence.push_back(Direction::left);
	moveSequence.push_back(Direction::up);
	AppendToVector(moveSequence, FormStraightSequence(9, Direction::left));
	moveSequence.push_back(Direction::down);
	AppendToVector(moveSequence, FormStraightSequence(2, Direction::right));

	int stepCount = 0;
	for (auto& move : moveSequence) {
		stepCount++;
		levelZero.ProcessTurn(move);
		std::cerr << "Baba is at (" << baba->GetXPos() << ", " << baba->GetYPos() << ")\n";
	}

	EXPECT_FALSE(levelZero.GetIsWon());
	levelZero.ProcessTurn(Direction::right);
	EXPECT_TRUE(levelZero.GetIsWon());

	std::vector<Entity*> entities = levelZero.GetAllEntities();
	for (auto& e : entities) {
		std::cerr << NounToString(e->GetType()) << "(" << e->GetXPos() << ", " << e->GetYPos() << ")";
		if (e->GetTextType().has_value()) {
			std::cerr << ": " << TextTypeToString(e->GetTextType().value());
		}
		if (e->GetNoun().has_value()) {
			std::cerr << " " << NounToString(e->GetNoun().value());
		}
		if (e->GetReferredProperty().has_value()) {
			std::cerr << " " << PropertyToString(e->GetReferredProperty().value());
		}
		std::cerr << "\n";
	}
}