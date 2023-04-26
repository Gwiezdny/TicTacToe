#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

Engine::Engine() {

    for (int i = 0; i < mapSizeY; i++) {
        for (int j = 0; j < mapSizeX; j++) {
            map[i][j].object.setSize(map[i][j].sizeVector);
            map[i][j].object.setFillColor(sf::Color::White);
            map[i][j].object.setPosition(map[i][j].sizeX * j + 8 * (j + 1), map[i][j].sizeY * i + 8 * (i + 1));
        }
    }

    if (!textureX.loadFromFile("assets/X.png")) { std::cout << "Texture loading failed...\n"; }
    if (!textureY.loadFromFile("assets/Y.png")) { std::cout << "Texture loading failed...\n"; }
}

void Engine::gameLoop() {
    RenderWindow window{ VideoMode{416, 416},"okienko"};
    window.setFramerateLimit(60);
    Event event;
    char playerTurn = 'X';

    const auto renderer = [this, &window] () { // od c++14 (ciekawostka)
        for (int i = 0; i < mapSizeY; i++) {
            for (int j = 0; j < mapSizeX; j++) {
                window.draw(map[i][j]);
            }
        }
    };

    const auto checkWin = [this]() -> bool {
        int winScore = 0;

        for (int i = 0; i < mapSizeY; i++) { //Sprawdza wygran¹ poziomo
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

        for (int i = 0; i < mapSizeX; i++) { //Sprawdza wygran¹ pionowo
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

        for (int i = 0; i <= mapSizeX - forWin; i++) { //Sprawdza wygran¹ ukoœnie lewostronnie
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

        for (int i = mapSizeX - 1; i >= mapSizeX - 1; i--) { //Sprawdza wygran¹ ukoœnie prawostronnie
            for (int j = 0; j <= mapSizeY - forWin; j++) {
                for (int l = 1; l < forWin; l++) {
                    if (map[i][j].sign != ' ' && map[i][j].sign == map[i - l][j + l].sign) {
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
        return false;
    };

    ////////////////////////////////////////

    while (true) {
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
                                }
                                else if (playerTurn == 'O') {
                                    map[i][j].object.setTexture(&textureY);
                                    map[i][j].sign = playerTurn;
                                    playerTurn = 'X';
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
            break;
        }
    }
}