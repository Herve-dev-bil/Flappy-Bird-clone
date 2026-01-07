#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();

    // 1. Initialiser SDL et créer la fenêtre
    bool Initialize();

    // 2. Nettoyer l'écran (mettre le fond bleu)
    void BeginDraw();

    // 3. Afficher le résultat final
    void EndDraw();

    // 4. Dessiner un rectangle (pour notre oiseau)
    // On passe un pointeur FRect pour la position et une couleur (r,g,b,a)
    void DrawRect(const SDL_FRect* rect, float r, float g, float b, float a);

    // 5. Fermer SDL proprement
    void Shutdown();

private:
    SDL_Window* mWindow;
    SDL_Renderer* mSDLRenderer;
};

#endif