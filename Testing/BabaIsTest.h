#pragma once
#include "../NotBabaIsYou/Entity.h"
#include "../NotBabaIsYou/Level.h"

// Utilities to make setting up tests easier
class BabaIsTest : public testing::Test {
protected:
	std::vector<InitialEntityDetails> ConstructRule(Noun n, Property p, int startX, int startY, bool makeVertical);
	std::vector<InitialEntityDetails> ConstructTransformationRule(Noun fromType, Noun toType, int startX, int startY, bool makeVertical);
	std::vector<InitialEntityDetails> ConstructFilledArea(Noun n, int bottomLeftCornerX, int bottomLeftCornerY, int width, int height);

	void AppendToVector(std::vector<InitialEntityDetails>& receiving, std::vector<InitialEntityDetails>& source);
	void AppendToVector(std::vector<Direction>& receiving, std::vector<Direction>& source);

	std::vector<Direction> FormStraightSequence(int length, Direction direction);
	std::vector<Direction> FormNudgeSequence(int nudgeDepth, Direction pushTowards);
	std::vector<Direction> FormMultiNudgeSequence(int nudgeDepth, int length, Direction pushTowards, Direction moveAlong);

private:
	Direction GetOpposite(Direction d);
};