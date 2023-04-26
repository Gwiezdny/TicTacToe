#include "engine.h"
#include "Place.h"

int main()
{
    while (true) {
        Engine Engine;
        Engine.gameLoop();

        if (Engine.gameover == false) {
            break;
        }
    }
}