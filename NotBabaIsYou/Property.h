#pragma once

enum class Property {
	you,
	stop,
	push,
	win
};

inline std::string PropertyToString(Property p) {
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