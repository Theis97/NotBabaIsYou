#include "pch.h"
#include "BabaIsTest.h"

std::vector<InitialEntityDetails> BabaIsTest::ConstructRule(Noun n, Property p, int startX, int startY, bool makeVertical) {
	std::vector<InitialEntityDetails> entityInfo;

	if (makeVertical) {
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, n });
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX, startY-1, TextType::is });
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX, startY-2, TextType::property, std::nullopt, p });
	}
	else {
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX, startY, TextType::noun, n });
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX+1, startY, TextType::is });
		entityInfo.push_back(InitialEntityDetails{ Noun::text, startX+2, startY, TextType::property, std::nullopt, p });
	}
	
	return entityInfo;
}

void BabaIsTest::AddToVector(std::vector<InitialEntityDetails>& receiving, std::vector<InitialEntityDetails>& source) {
	// TODO: allow this add an arbitrary number of vectors
	receiving.insert(receiving.end(), source.begin(), source.end());
}