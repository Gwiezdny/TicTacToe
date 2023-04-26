#pragma once
#include <SFML/Graphics.hpp>

class Place : public sf::Drawable {

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::RectangleShape object;

	const int sizeX{ 128 };
	const int sizeY{ 128 };
	sf::Vector2f sizeVector{ sizeX, sizeY };

	//Place() = delete;
	//~Place() = delete;

	char sign{};
};