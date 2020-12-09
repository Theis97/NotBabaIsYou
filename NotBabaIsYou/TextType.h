#pragma once

enum class TextType {
	noun,
	is, 
	property
};

inline std::string TextTypeToString(TextType t) {
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