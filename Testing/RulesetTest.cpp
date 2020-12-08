#include "pch.h"
#include "../NotBabaIsYou/Ruleset.h"

TEST(RulesetTest, TestRuleParsing) {
	Ruleset rules = Ruleset();

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity youText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&youText);

	rules.ParseRule(textChunks);
	ASSERT_FALSE(rules.GetNounsToProperties().empty());
	ASSERT_TRUE(rules.IsEntityProperty(Noun::baba, Property::you));
}