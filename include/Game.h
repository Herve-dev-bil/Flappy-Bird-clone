#ifndef GAME_H
#define GAME_H

#include <vector> //Pour la liste
#include "Pipe.h"

#include <SDL3/SDL.h>
#include "Bird.h"
class Game
{
public:
  Game();
  ~Game();
  void Run();

  int mScore; // LE SCORE

private:
  void ProcessInput();
  void Update(float deltaTime);
  void GenerateOutput();

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  bool mIsRunning;
  bool game_paused;

  Bird *mBird;
 

  SDL_Texture *mTexBackground; // L'image du ciel
  SDL_Texture *mTexGround;     // L'image du sol
  SDL_Texture *mTexPipe;       // image du tuyau
  float mGroundX;

  // GESTION DES TUYAUX
  std::vector<Pipe *> mPipes; // La liste de tous les tuyaux à l'écran
  float mPipeSpawnTimer;      // Compte à rebours pour le prochain tuyau

  SDL_Texture *LoadTexture(const char *fileName);
};

#endif