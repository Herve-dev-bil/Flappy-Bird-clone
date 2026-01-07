#ifndef GAME_H
#define GAME_H

#include "Renderer.h" // On inclut notre nouveau module
#include "Bird.h"

class Game {
public:
    Game();
    ~Game();
    bool Initialize(); // Nouvelle fonction pour démarrer proprement
    void Run();

private:
    void ProcessInput();
    void Update(float deltaTime);
    void GenerateOutput();

    Renderer* mRenderer; // <--- On utilise  classe Renderer
    Bird* mBird;
    bool mIsRunning;
};

#endif