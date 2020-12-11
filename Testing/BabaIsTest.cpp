#include "pch.h"
#include "BabaIsTest.h"

std::vector<InitialEntityDetails> BabaIsTest::ConstructRule(Noun n, Property p, int startX, int startY, bool makeVertical) {
	std::vector<InitialEntityDetails> entityDetails;

	if (makeVertical) {
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, n });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY-1, TextType::is });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY-2, TextType::property, std::nullopt, p });
	}
	else {
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, n });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX+1, startY, TextType::is });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX+2, startY, TextType::property, std::nullopt, p });
	}
	
	return entityDetails;
}

std::vector<InitialEntityDetails> BabaIsTest::ConstructTransformationRule(Noun fromType, Noun toType, int startX, int startY, bool makeVertical) {
	std::vector<InitialEntityDetails> entityDetails;

	if (makeVertical) {
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, fromType });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY - 1, TextType::is });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY - 2, TextType::noun, toType});
	}
	else {
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, fromType });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX + 1, startY, TextType::is });
		entityDetails.push_back(InitialEntityDetails{ Noun::text, startX + 2, startY, TextType::noun, toType });
	}

	return entityDetails;
}

// Don't try to use this function with text. Why would you even want to?
std::vector<InitialEntityDetails> BabaIsTest::ConstructFilledArea(Noun n, int bottomLeftCornerX, int bottomLeftCornerY, int width, int height) {
	std::vector<InitialEntityDetails> entityDetails;

	for (int x = bottomLeftCornerX; x < bottomLeftCornerX + width; x++) {
		for (int y = bottomLeftCornerY; y < bottomLeftCornerY + height; y++) {
			entityDetails.push_back(InitialEntityDetails{ n, x, y });
		}
	}
	return entityDetails;
}



void BabaIsTest::AppendToVector(std::vector<InitialEntityDetails>& receiving, std::vector<InitialEntityDetails>& source) {
	receiving.insert(receiving.end(), source.begin(), source.end());
}

void BabaIsTest::AppendToVector(std::vector<Direction>& receiving, std::vector<Direction>& source) {
	receiving.insert(receiving.end(), source.begin(), source.end());
}

std::vector<Direction> BabaIsTest::FormStraightSequence(int length, Direction direction) {
	std::vector<Direction> sequence;
	for (int i = 0; i < length; i++) {
		sequence.push_back(direction);
	}
	return sequence;
}

std::vector<Direction> BabaIsTest::FormNudgeSequence(int nudgeDepth, Direction pushTowards) {
	std::vector<Direction> result = FormStraightSequence(nudgeDepth, pushTowards);
	AppendToVector(result, FormStraightSequence(nudgeDepth, GetOpposite(pushTowards)));
	return result;
}

std::vector<Direction> BabaIsTest::FormMultiNudgeSequence(int nudgeDepth, int length, Direction pushTowards, Direction moveAlong) {
	std::vector<Direction> result;
	for (int i = 0; i < length; i++) {
		result.push_back(moveAlong);
		AppendToVector(result, FormNudgeSequence(nudgeDepth, pushTowards));
	}
	return result;
}

std::string BabaIsTest::NounToString(Noun n) {
	std::string s;
	switch (n) {
	case Noun::baba:
		s = "Baba";
		break;
	case Noun::flag:
		s = "Flag";
		break;
	case Noun::rock:
		s = "Rock";
		break;
	case Noun::wall:
		s = "Wall";
		break;
	case Noun::text:
		s = "Text";
		break;
	}
	return s;
}

std::string BabaIsTest::PropertyToString(Property p) {
	std::string s;
	switch (p) {
	case Property::you:
		s = "You";
		break;
	case Property::stop:
		s = "Stop";
		break;
	case Property::push:
		s = "Push";
		break;
	case Property::win:
		s = "Win";
		break;
	}
	return s;
}

std::string BabaIsTest::TextTypeToString(TextType t) {
	std::string s;
	switch (t) {
	case TextType::noun:
		s = "Noun";
		break;
	case TextType::is:
		s = "Is";
		break;
	case TextType::property:
		s = "Property";
		break;
	}
	return s;
}

Direction BabaIsTest::GetOpposite(Direction d) {
	Direction opposite = Direction::down;
	switch (d) {
	case Direction::up:
		opposite = Direction::down;
		break;
	case Direction::right:
		opposite = Direction::left;
		break;
	case Direction::down:
		opposite = Direction::up;
		break;
	case Direction::left:
		opposite = Direction::right;
		break;
	}
	return opposite;
}
