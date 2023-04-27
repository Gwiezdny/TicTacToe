#include "engine.h"
#include "Place.h"

int main()
{
    int scoreX{ 0 };
    int scoreO{ 0 };

    while (true) {
        Engine Engine(&scoreX, &scoreO);
        Engine.gameLoop();

        if (Engine.gameover == false) {
            break;
        }
    }
}