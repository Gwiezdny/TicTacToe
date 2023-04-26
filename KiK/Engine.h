#pragma once
#include <array>
#include "Place.h"

class Engine
{
	static const int mapSizeX = 3;
	static const int mapSizeY = 3;
	static const int forWin = 3;

	sf::Texture textureX;
	sf::Texture textureY;

	std::array<std::array<Place, mapSizeX>, mapSizeY> map;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											;
public:
	bool gameover = false;

	void gameLoop();
	Engine();
};
