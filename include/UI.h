#ifndef UI_H
#define UI_H

#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

// Les états possibles du jeu
enum GameState
{
    STATE_MENU,     // Écran d'accueil: Le jeu est en pause, on attend le joueur
    STATE_PLAYING,  // En train de jouer,: Le jeu tourne, l'oiseau tombe
    STATE_GAME_OVER // Perdu: L'oiseau est mort, on affiche le score final
};
// ------------------------------------------

class UI
{
public:
   // Initialisation d'ImGui
    void Init(SDL_Window* window, SDL_Renderer* renderer);
    
    // Nettoyage à la fin
    void Shutdown();
    
    // Gérer les clics et le clavier pour l'interface
    void ProcessEvent(SDL_Event* event);

    //passage de l'état du jeu (state)
    // Dessiner l'interface
    //utilisation des références (bool&) pour renvoyer les ordres au jeu (Reset ou Quitter)
    void Draw(SDL_Renderer* renderer, GameState state, int score, int highScore, bool &startGame, bool &restart, bool &quit);
};

#endif