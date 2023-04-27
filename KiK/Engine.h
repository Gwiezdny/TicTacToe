#pragma once
#include <array>
#include "Place.h"

class Engine
{
	static const int mapSizeX = 4; // Rozmiar mapy w osi X
	static const int mapSizeY = 4; // Rozmiar mapy w osi Y
	static const int forWin = 3; // Wymagana liczba powtórzonych znaków wymagana do wygranej 

	sf::Texture textureX;
	sf::Texture textureO;

	std::array<std::array<Place, mapSizeX>, mapSizeY> map;		
	Place playerTurnPlace;
public:
	bool gameover = false;

	void gameLoop();
	Engine();
};
