#pragma once
#include "Place.h"

class Engine
{
	static const int x = 3;
	static const int y = 3;
	static const int forWin = 3;

	int map[x][y];
	Place lol(5, 5);

	int checkWin();

public:
	void gameLoop();
};

