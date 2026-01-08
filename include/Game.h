#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include "Bird.h"
class Game
{
public:
    Game();
    ~Game();
    void Run();

private:

  void ProcessInput();
  void Update(float deltaTime);
  void GenerateOutput();

  SDL_Window* mWindow;
  SDL_Renderer* mRenderer;
  bool mIsRunning;

  Bird* mBird;
};



#endif