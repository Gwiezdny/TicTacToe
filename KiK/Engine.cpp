#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

void Engine::gameLoop() {
    RenderWindow window{ VideoMode{800,600},"okienko" };
    window.setFramerateLimit(60);
    Event event;

    //Place lol(5, 5);

    while (true) {
        window.clear(Color::Black);
        window.pollEvent(event);

        if (event.type == Event::Closed) {
            window.close();
            break;
        }

        //window.draw(bullet);
        window.display();
    }
}

int Engine::checkWin() {
    int winScore = 0;

    for (int i = 0; i < y; i++) { //Sprawdza wygran¹ poziomo
        for (int j = 0; j <= x - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[j][i] == map[j + l][i]) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[j][i];
                    }
                }
                else {
                    winScore = 0;
                    l = forWin;//przerwanie petli
                }
            }
        }
    }

    for (int i = 0; i < x; i++) { //Sprawdza wygran¹ pionowo
        for (int j = 0; j <= y - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[i][j] == map[i][j + l]) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j];
                    }
                }
                else {
                    winScore = 0;
                    l = forWin;//przerwanie petli
                }
            }
        }
    }

    for (int i = 0; i <= x - forWin; i++) { //Sprawdza wygran¹ ukoœnie lewostronnie
        for (int j = 0; j <= y - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[i][j] == map[i + l][j + l]) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j];
                    }
                }
                else {
                    winScore = 0;
                    l = forWin;//przerwanie petli
                }
            }
        }
    }

    for (int i = x - 1; i >= 0; i--) { //Sprawdza wygran¹ ukoœnie prawostronnie
        for (int j = 0; j <= y - forWin; j++) {
            for (int l = 1; l < forWin; l++) {
                if (map[i][j] == map[i - l][j + l]) {
                    winScore++;
                    if (winScore == forWin - 1) {
                        winScore = 0;
                        return map[i][j];
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