#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <windows.h>

using namespace sf;

Engine::Engine() {
    if (!textureX.loadFromFile("assets/X.png")) { std::cout << "Texture loading failed...\n"; }
    if (!textureO.loadFromFile("assets/Y.png")) { std::cout << "Texture loading failed...\n"; }

    for (int i = 0; i < mapSizeY; i++) {
        for (int j = 0; j < mapSizeX; j++) {
            map[i][j].object.setSize(map[i][j].sizeVector);
            map[i][j].object.setFillColor(sf::Color::White);
            map[i][j].object.setPosition((float)map[i][j].sizeX * j + 8 * (j + 1), (float)map[i][j].sizeY * ( i + 1 ) + 8 * (i + 3));
        }
    }

    playerTurnPlace.object.setSize(playerTurnPlace.sizeVector);
    playerTurnPlace.object.setOrigin(playerTurnPlace.sizeX / 2, 0);
    playerTurnPlace.object.setPosition((float)(map[0][0].sizeX * mapSizeX + 8 * (mapSizeX + 1)) / 2, 8);
    playerTurnPlace.object.setTexture(&textureX);
}

void Engine::gameLoop() {
    RenderWindow window{ VideoMode{(unsigned int) map[0][0].sizeX * mapSizeX + 8 * (mapSizeX + 1), (unsigned int) map[0][0].sizeY * ( mapSizeY + 1 ) + 8 * (mapSizeY + 3)},"okienko"};
    window.setFramerateLimit(60);
    Event event;
    char playerTurn = 'X';

    const auto renderer = [this, &window] () { // od c++14 (ciekawostka)
        window.draw(playerTurnPlace);

        for (int i = 0; i < mapSizeY; i++) {
            for (int j = 0; j < mapSizeX; j++) {
                window.draw(map[i][j]);
            }
        }
    };

    const auto checkWin = [this]() -> bool {
        int winScore{ 0 };
        int checkScore{ 0 };

        for (int i = 0; i < mapSizeY; i++) { //Sprawdza wygran� poziomo
            for (int j = 0; j <= mapSizeX - forWin; j++) {
                for (int l = 1; l < forWin; l++) {
                    if (map[j][i].sign != ' ' && map[j][i].sign == map[j + l][i].sign) {
                        winScore++;
                        if (winScore == forWin - 1) {
                            winScore = 0;
                            std::cout << "Wygrywa: " << map[j][i].sign << std::endl;
                            return true;
                        }
                    }
                    else {
                        winScore = 0;
                        l = forWin;//przerwanie petli
                    }
                }
            }
        }

        for (int i = 0; i < mapSizeX; i++) { //Sprawdza wygran� pionowo
            for (int j = 0; j <= mapSizeY - forWin; j++) {
                for (int l = 1; l < forWin; l++) {
                    if (map[i][j].sign != ' ' && map[i][j].sign == map[i][j + l].sign) {
                        winScore++;
                        if (winScore == forWin - 1) {
                            winScore = 0;
                            std::cout << "Wygrywa: " << map[i][j].sign << std::endl;
                            return true;
                        }
                    }
                    else {
                        winScore = 0;
                        l = forWin;//przerwanie petli
                    }
                }
            }
        }

        for (int i = 0; i <= mapSizeX - forWin; i++) { //Sprawdza wygran� uko�nie lewostronnie
            for (int j = 0; j <= mapSizeY - forWin; j++) {
                for (int l = 1; l < forWin; l++) {
                    if (map[i][j].sign != ' ' && map[i][j].sign == map[i + l][j + l].sign) {
                        winScore++;
                        if (winScore == forWin - 1) {
                            winScore = 0;
                            std::cout << "Wygrywa: " << map[i][j].sign << std::endl;
                            return true;
                        }
                    }
                    else {
                        winScore = 0;
                        l = forWin;//przerwanie petli
                    }
                }
            }
        }

        for (int i = mapSizeX - 1; i >= forWin - 1; i--) { //Sprawdza wygran� uko�nie prawostronnie
            for (int j = 0; j <= mapSizeY - forWin; j++) {
                for (int l = 1; l < forWin; l++) {
                    if (map[j][i].sign != ' ' && map[j][i].sign == map[j + l][i - l].sign) {
                        winScore++;
                        if (winScore == forWin - 1) {
                            winScore = 0;
                            std::cout << "Wygrywa: " << map[j][i].sign << std::endl;
                            return true;
                        }
                    }
                    else {
                        winScore = 0;
                        l = forWin;//przerwanie petli
                    }
                }
            }
        }

        for (int i = 0; i < mapSizeY; i++) {
            for (int j = 0; j < mapSizeX; j++) {
                if (map[j][i].sign != ' ') { checkScore++; }
            }
        }
        if (checkScore == mapSizeX * mapSizeY) {
            std::cout << "remis\n";
            return true;
        }

        return false;
    };

    ////////////////////////////////////////

    while (true) { //gl�wna p�tla
        if (gameover == false) {
            window.clear(Color::Black);
            window.pollEvent(event);
            sf::Vector2i mousePos = Mouse::getPosition(window);
            bool isMouseClicked = Mouse::isButtonPressed(sf::Mouse::Left);

            if (event.type == Event::Closed) {
                window.close();
                break;
            }

            for (int i = 0; i < mapSizeY; i++) {
                for (int j = 0; j < mapSizeX; j++) {
                    if (map[i][j].object.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        if (isMouseClicked) {
                            if (map[i][j].sign == ' ') {

                                if (playerTurn == 'X') {
                                    map[i][j].object.setTexture(&textureX);
                                    map[i][j].sign = playerTurn;
                                    playerTurn = 'O';
                                    playerTurnPlace.object.setTexture(&textureO);
                                }
                                else if (playerTurn == 'O') {
                                    map[i][j].object.setTexture(&textureO);
                                    map[i][j].sign = playerTurn;
                                    playerTurn = 'X';
                                    playerTurnPlace.object.setTexture(&textureX);
                                }
                                gameover = checkWin();
                            }
                        }
                    }
                }
            }

            renderer();
            window.display();
        }
        else {
            Sleep(100);
            break;
        }
    }
}