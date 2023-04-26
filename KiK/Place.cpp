#include "Place.h"

void Place::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(this->object, state);
}