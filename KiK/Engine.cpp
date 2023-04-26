#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include "Place.h"

using namespace sf;

Engine::Engine() {

    for (int i = 0; i < mapSizeY; i++) {
        for (int j = 0; j < mapSizeX; j++) {
            map[i][j].object.setSize(map[i][j].sizeVector);
            map[i][j].object.setFillColor(sf::Color::White);
            map[i][j].object.setPosition(map[i][j].sizeX * j + 8 * (j + 1), map[i][j].sizeY * i + 8 * (i + 1));
        }
    }
}

void Engine::gameLoop() {
    RenderWindow window{ VideoMode{800,600},"okienko" };
    window.setFramerateLimit(60);
    Event event;

    while (true) {
        window.clear(Color::Black);
        window.pollEvent(event);

        if (event.type == Event::Closed) {
            window.close();
            break;
        }

        //renderer();

        for (int i = 0; i < mapSizeY; i++) {
            for (int j = 0; j < mapSizeX; j++) {
                window.draw(map[i][j]);
            }
        }

        window.display();

    }
}

void renderer() {

}

int Engine::checkWin() {
    int winScore = 0;

    for (int i = 0; i < mapSizeY; i++) { //Sprawdza wygran¹ poziomo
        for (int j = 0; j <= mapSizeX - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[j][i].sign == map[j + l][i].sign) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[j][i].sign;
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
                if (map[i][j].sign == map[i][j + l].sign) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j].sign;
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
                if (map[i][j].sign == map[i + l][j + l].sign) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j].sign;
                    }
                }
                else {
                    winScore = 0;
                    l = forWin;//przerwanie petli
                }
            }
        }
    }

    for (int i = mapSizeX - 1; i >= 0; i--) { //Sprawdza wygran¹ ukoœnie prawostronnie
        for (int j = 0; j <= mapSizeY - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[i][j].sign == map[i - l][j + l].sign) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j].sign;
                    }
                }
                else {
                    winScore = 0;
                    l = forWin;//przerwanie petli
                }
            }
        }
    }
}