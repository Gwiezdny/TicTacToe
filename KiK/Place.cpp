#include "Place.h"

Place::Place(float x, float y) {
	object.setSize(sizeVector);
	object.setFillColor(sf::Color::Red);
	object.setPosition(x, y);
}