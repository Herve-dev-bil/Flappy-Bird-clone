#ifndef GAME_H
#define GAME_H

#include <vector> //Pour la liste
#include "Pipe.h"

#include <SDL3/SDL.h>
#include "Bird.h"
#include "UI.h"
class Game
{
public:
  Game();
  ~Game();
  void Run();

  // Ajout  d'un "getter" pour que l'UI puisse afficher le record
  int GetHighScore() const { return mHighScore; }

private:
  void ProcessInput();
  void Update(float deltaTime);
  void GenerateOutput();
  void RestartGame();


  void LoadHighScore(); // Lire le fichier au démarrage
  void SaveHighScore(); // Écrire dans le fichier quand on gagne

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  bool mIsRunning;
  
  GameState mState;

  Bird *mBird;

  int mScore;     // LE SCORE
  int mHighScore; // Le Record (sauvegardé)

  //L'instance de l'interface
  UI mUI;

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