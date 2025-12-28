#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>

class Game {
public:
    Game();  // Constructeur (Initialisation)
    ~Game(); // Destructeur (Nettoyage)
    void Run();

private:
    void ProcessInput();
    void Update();
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
};

#endif