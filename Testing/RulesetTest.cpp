#include "pch.h"
#include "BabaIsTest.h"
#include "../NotBabaIsYou/Ruleset.h"


class RulesetTest : public BabaIsTest {};

TEST_F(RulesetTest, BasicRuleParsing) {
	Ruleset rules = Ruleset();

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity youText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&youText);

	rules.ParseRule(textChunks);
	ASSERT_FALSE(rules.GetPropertyRules().empty());
	EXPECT_TRUE(rules.DoesTypeHaveProperty(Noun::baba, Property::you));
}

TEST_F(RulesetTest, RulesResetProperly) {
	Ruleset rules = Ruleset();

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity youText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::property, std::nullopt, Property::you });
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&youText);

	rules.ParseRule(textChunks);
	
	EXPECT_TRUE(rules.DoesTypeHaveProperty(Noun::baba, Property::you));

	rules.Reset();
	EXPECT_FALSE(rules.DoesTypeHaveProperty(Noun::baba, Property::you));
}

TEST_F(RulesetTest, ParsingTransformationRules) {
	Ruleset rules = Ruleset();

	std::vector<Entity*> textChunks;

	Entity babaText = Entity(InitialEntityDetails{ Noun::text, 0, 2, TextType::noun, Noun::baba });
	Entity isText = Entity(InitialEntityDetails{ Noun::text, 1, 2, TextType::is });
	Entity flagText = Entity(InitialEntityDetails{ Noun::text, 2, 2, TextType::noun, Noun::flag});
	textChunks.push_back(&babaText);
	textChunks.push_back(&isText);
	textChunks.push_back(&flagText);

	rules.ParseRule(textChunks);
	std::map<Noun, std::set<Noun>> transformations = rules.GetTransformationRules();
	ASSERT_FALSE(transformations.empty());

	std::set<Noun> babaTransformations = transformations[Noun::baba];
	ASSERT_FALSE(babaTransformations.empty());
	EXPECT_NE(babaTransformations.find(Noun::flag), babaTransformations.end());
}