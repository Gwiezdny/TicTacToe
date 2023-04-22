#pragma once
#include <SFML/Graphics.hpp>

class Place:public sf::Drawable {
	sf::RectangleShape object;

	const int sizeX{ 10 };
	const int sizeY{ 10 };
	const float positionX{ 5.0f };
	const float positionY{ 5.0f };
	sf::Vector2f sizeVector{ sizeX,sizeY };

public:
	Place(float x, float y);
	Place() = delete;
	//~Place() = delete;
};

