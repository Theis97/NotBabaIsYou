#pragma once

// Used to neatly initialize Entities
struct InitialEntityDetails {
	Noun type{};
	int x{};
	int y{};
	std::optional<TextType> textType;
	std::optional<Noun> noun;
	std::optional<Property> prop;
};