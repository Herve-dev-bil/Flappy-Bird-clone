#ifndef PIPE_H
#define PIPE_H

#include <SDL3/SDL.h>

class Pipe {
public:
    // On construit le tuyau à une position X précise
    Pipe(float startX);

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    // Pour savoir si le tuyau est sorti de l'écran
    bool IsOffScreen();

    // Pour accéder à la position (collisions)
    float GetX() { return mX; }
    float GetWidth() { return width; }

private:
    float mX;       //  horizontale
    float mGapY;    // Hauteur 
    
    // Constantes (Règles du jeu)
    const float width = 60.0f;       // Largeur du tuyau
    const float speed = 300.0f;      // Vitesse 
    const float gapSize = 150.0f;    // Taille du trou pour passer
};

#endif