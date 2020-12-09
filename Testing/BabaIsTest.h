#pragma once
#include "../NotBabaIsYou/Entity.h"

// Utilities to make setting up tests easier
class BabaIsTest : public testing::Test {
protected:
	std::vector<InitialEntityDetails> ConstructRule(Noun n, Property p, int startX, int startY, bool makeVertical);

	void AddToVector(std::vector<InitialEntityDetails>& receiving, std::vector<InitialEntityDetails>& source);
};