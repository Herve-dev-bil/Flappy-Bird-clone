#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    game.Run(); // Lance la boucle infinie du jeu
    return 0;
}