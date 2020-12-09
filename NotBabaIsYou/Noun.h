#pragma once

enum class Noun {
	baba,
	rock,
	flag,
	wall,
	text
};

inline std::string NounToString(Noun n) {
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