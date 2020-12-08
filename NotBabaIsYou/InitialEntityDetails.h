#pragma once

struct InitialEntityDetails {
	Noun type{};
	int x{};
	int y{};
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> prop;
};