#pragma once
#include <array>
#include "Place.h"

class Engine
{
	static const int mapSizeX = 3;
	static const int mapSizeY = 3;
	static const int forWin = 3;

	std::array<std::array<Place, mapSizeX>, mapSizeY> map;

	sf::Mouse mouse																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												;

	int checkWin();

public:
	void gameLoop();
	//void renderer();
	Engine();
};
