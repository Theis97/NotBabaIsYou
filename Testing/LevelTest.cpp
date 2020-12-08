#include "pch.h"
#include "../NotBabaIsYou/Level.h"

TEST(LevelTest, TestTextSegmentsChecked) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });

	entities.push_back(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	entities.push_back(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });

	Level lvl = Level(width, height, entities);

	int testSegmentsChecked = lvl.UpdateRules();
	ASSERT_EQ(testSegmentsChecked, 4);
}