#include "pch.h"
#include "BabaIsTest.h"

// This test suite tests the correctness of particular behaviors of the game engine
class BehaviorTest : public BabaIsTest {};
TEST_F(BehaviorTest, BasicMovement) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });

	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 2, false);
	AppendToVector(entities, babaIsYou);

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();

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
	AppendToVector(entities, babaIsYou);
	AppendToVector(entities, rockIsPush);

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 2, 2 });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			EXPECT_EQ(e->GetXPos(), 2);
			EXPECT_EQ(e->GetYPos(), 2);
		}
		if (e->GetType() == Noun::rock) {
			EXPECT_EQ(e->GetXPos(), 3);
			EXPECT_EQ(e->GetYPos(), 2);
		}
	}
}

TEST_F(BehaviorTest, PushAndStop) {
	int width = 6;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 4, false));
	AppendToVector(entities, ConstructRule(Noun::rock, Property::push, 0, 0, false));
	AppendToVector(entities, ConstructRule(Noun::rock, Property::stop, 3, 0, false));

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 2, 2 });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			EXPECT_EQ(e->GetXPos(), 2);
			EXPECT_EQ(e->GetYPos(), 2);
		}
		if (e->GetType() == Noun::rock) {
			EXPECT_EQ(e->GetXPos(), 3);
			EXPECT_EQ(e->GetYPos(), 2);
		}
	}
}

TEST_F(BehaviorTest, PushText) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 4, false));

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 2, TextType::noun, Noun::rock });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			EXPECT_EQ(e->GetXPos(), 2);
			EXPECT_EQ(e->GetYPos(), 2);
		}
		if (e->GetType() == Noun::rock) {
			EXPECT_EQ(e->GetXPos(), 3);
			EXPECT_EQ(e->GetYPos(), 2);
		}
	}
}

TEST_F(BehaviorTest, WinCheckWorks) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 2, false);
	std::vector<InitialEntityDetails> flagIsWin = ConstructRule(Noun::flag, Property::win, 0, 0, false);
	AppendToVector(entities, babaIsYou);
	AppendToVector(entities, flagIsWin);

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });
	entities.push_back(InitialEntityDetails{ Noun::flag, 2, 1 });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

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
	ASSERT_TRUE(rules->DoesTypeHaveProperty(Noun::baba, Property::you));
	ASSERT_TRUE(rules->DoesTypeHaveProperty(Noun::flag, Property::win));

	ASSERT_TRUE(lvl.GetIsWon());
}

TEST_F(BehaviorTest, StayInbounds) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });

	std::vector<InitialEntityDetails> babaIsYou = ConstructRule(Noun::baba, Property::you, 0, 2, false);
	AppendToVector(entities, babaIsYou);

	Level lvl = Level(width, height, entities);

	for (int i = 0; i < 10; i++) {
		lvl.ProcessTurn(Direction::left);
	}

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 0);
			ASSERT_EQ(e->GetYPos(), 1);
		}
	}

}

TEST_F(BehaviorTest, PushIntoSolidObject) {
	int width = 3;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 4, true));
	AppendToVector(entities, ConstructRule(Noun::wall, Property::stop, 1, 4, true));
	AppendToVector(entities, ConstructRule(Noun::rock, Property::push, 2, 4, true));

	entities.push_back(InitialEntityDetails{ Noun::baba, 2, 0 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 1, 0 });
	entities.push_back(InitialEntityDetails{ Noun::wall, 0, 0 });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::left);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 0);
		}
		if (e->GetType() == Noun::rock) {
			ASSERT_EQ(e->GetXPos(), 1);
			ASSERT_EQ(e->GetYPos(), 0);
		}
		if (e->GetType() == Noun::wall) {
			ASSERT_EQ(e->GetXPos(), 0);
			ASSERT_EQ(e->GetYPos(), 0);
		}
	}
}

TEST_F(BehaviorTest, BabaIsNotYou) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 1, false));
	entities.push_back(InitialEntityDetails{ Noun::baba, 2, 0});

	Level lvl = Level(width, height, entities);

	bool youExist = lvl.DoYouExist();
	EXPECT_TRUE(youExist);

	lvl.ProcessTurn(Direction::up);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			ASSERT_EQ(e->GetXPos(), 2);
			ASSERT_EQ(e->GetYPos(), 1);
		}
	}

	Ruleset* rules = lvl.GetRules();
	EXPECT_TRUE(rules->DoesTypeHaveProperty(Noun::text, Property::push));
	EXPECT_FALSE(rules->DoesTypeHaveProperty(Noun::baba, Property::you));

	lvl.ProcessTurn(Direction::down);
	youExist = lvl.DoYouExist();
	EXPECT_FALSE(youExist);

	inLevelEntities = lvl.GetAllEntities();
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			EXPECT_EQ(e->GetXPos(), 2);
			EXPECT_EQ(e->GetYPos(), 1);
		}
	}
}

TEST_F(BehaviorTest, YouIsStopMovement) {
	int width = 3;
	int height = 3;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 2, false));
	entities.push_back(InitialEntityDetails{ Noun::text, 0, 1, TextType::is});
	entities.push_back(InitialEntityDetails{ Noun::text, 0, 0, TextType::property, std::nullopt, Property::stop});
	
	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 1 });
	entities.push_back(InitialEntityDetails{ Noun::baba, 2, 1 });
	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 0 });
	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 0 });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);

	std::vector<Entity*> inLevelEntities = lvl.GetAllEntities();
	int babaCounts[3][3] = {0};
	for (auto& e : inLevelEntities) {
		if (e->GetType() == Noun::baba) {
			babaCounts[e->GetXPos()][e->GetYPos()]++;
		}
	}
	ASSERT_EQ(babaCounts[1][1], 1);
	ASSERT_EQ(babaCounts[2][1], 1);
	ASSERT_EQ(babaCounts[2][0], 2);
}

TEST_F(BehaviorTest, StopAndNotStop) {
	int width = 3;
	int height = 6;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::wall, Property::stop, 1, 3, true));
	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 0, 0, false));
	AppendToVector(entities, ConstructFilledArea(Noun::wall, 0, 4, 3, 1));
	entities.push_back(InitialEntityDetails{ Noun::baba, 2, 3});

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::up);

	std::vector<Entity*> tileEntities =  lvl.GetEntitiesAt(2, 3);
	ASSERT_FALSE(tileEntities.empty());
	ASSERT_TRUE(tileEntities[0]->GetType() == Noun::baba);

	lvl.ProcessTurn(Direction::left);
	lvl.ProcessTurn(Direction::up);
	lvl.ProcessTurn(Direction::up);

	tileEntities = lvl.GetEntitiesAt(1, 5);
	ASSERT_FALSE(tileEntities.empty());
	EXPECT_TRUE(tileEntities[0]->GetType() == Noun::baba);
}

TEST_F(BehaviorTest, BasicTransformation) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 1, 0, false));
	entities.push_back(InitialEntityDetails{ Noun::baba, 3, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::text, 1, 4, TextType::noun, Noun::rock });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 4, TextType::is });
	entities.push_back(InitialEntityDetails{ Noun::text, 3, 3, TextType::noun, Noun::flag });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::up);
	std::vector<Entity*> tileEntities = lvl.GetEntitiesAt(1, 2);
	ASSERT_EQ(tileEntities.size(), 1);
	EXPECT_EQ(tileEntities[0]->GetType(), Noun::flag);
}

TEST_F(BehaviorTest, ChainedTransformation) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 1, 0, false));
	AppendToVector(entities, ConstructTransformationRule(Noun::wall, Noun::flag, 2, 4, false));
	entities.push_back(InitialEntityDetails{ Noun::baba, 0, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::text, 0, 3, TextType::noun, Noun::rock });
	entities.push_back(InitialEntityDetails{ Noun::text, 1, 4, TextType::is });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::up);
	std::vector<Entity*> tileEntities = lvl.GetEntitiesAt(1, 2);
	ASSERT_EQ(tileEntities.size(), 1);
	EXPECT_EQ(tileEntities[0]->GetType(), Noun::wall);

	lvl.ProcessTurn(Direction::down);
	tileEntities = lvl.GetEntitiesAt(1, 2);
	ASSERT_EQ(tileEntities.size(), 1);
	EXPECT_EQ(tileEntities[0]->GetType(), Noun::flag);
}

TEST_F(BehaviorTest, DoubleTransformation) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 1, 0, false));
	entities.push_back(InitialEntityDetails{ Noun::baba, 0, 4 });
	entities.push_back(InitialEntityDetails{ Noun::wall, 4, 2 });
	entities.push_back(InitialEntityDetails{ Noun::text, 1, 4, TextType::noun, Noun::wall});
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 2, TextType::noun, Noun::rock });
	entities.push_back(InitialEntityDetails{ Noun::text, 4, 4, TextType::noun, Noun::flag });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 3, TextType::is});
	entities.push_back(InitialEntityDetails{ Noun::text, 3, 4, TextType::is });

	Level lvl = Level(width, height, entities);
	std::cerr << "Checkpoint 1\n";
	lvl.ProcessTurn(Direction::right);
	std::cerr << "Checkpoint 2\n";

	std::vector<Entity*> tileEntities = lvl.GetEntitiesAt(4, 2);
	ASSERT_EQ(tileEntities.size(), 2);

	int expectedTypeCount = 0;
	for (auto &e : tileEntities) {
		if (e->GetType() == Noun::flag || e->GetType() == Noun::rock) {
			expectedTypeCount++;
		}
	}
	ASSERT_EQ(expectedTypeCount, 2);
}

TEST_F(BehaviorTest, PreventTransformation) {
	int width = 5;
	int height = 5;
	std::vector<InitialEntityDetails> entities;

	AppendToVector(entities, ConstructRule(Noun::baba, Property::you, 1, 0, false));
	AppendToVector(entities, ConstructTransformationRule(Noun::rock, Noun::rock, 1, 4, false));
	entities.push_back(InitialEntityDetails{ Noun::baba, 1, 2 });
	entities.push_back(InitialEntityDetails{ Noun::rock, 0, 2 });
	entities.push_back(InitialEntityDetails{ Noun::text, 2, 2, TextType::noun, Noun::flag });
	entities.push_back(InitialEntityDetails{ Noun::text, 3, 3, TextType::is });

	Level lvl = Level(width, height, entities);

	lvl.ProcessTurn(Direction::right);
	std::vector<Entity*> tileEntities = lvl.GetEntitiesAt(0, 2);
	ASSERT_EQ(tileEntities.size(), 1);
	ASSERT_EQ(tileEntities[0]->GetType(), Noun::rock);

}