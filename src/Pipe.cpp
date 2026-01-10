#include "Pipe.h"
#include <cstdlib> // Pour rand() (nombres aléatoires)

Pipe::Pipe(float startX) {
    mX = startX;
    
    // On choisit une hauteur de trou aléatoire
    // Le trou sera entre 150px et 450px de hauteur
    mGapY = 150.0f + (rand() % 300); 
}

void Pipe::Update(float deltaTime) {
    // Le tuyau avance vers la gauche
    mX -= speed * deltaTime;
}

void Pipe::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // VERT

    // 1. Tuyau du HAUT
    // Il part de 0 (haut) et descend jusqu'au début du trou
    SDL_FRect topPipe;
    topPipe.x = mX;
    topPipe.y = 0;
    topPipe.w = width;
    topPipe.h = mGapY - (gapSize / 2); // S'arrête au début du trou
    SDL_RenderFillRect(renderer, &topPipe);

    // 2. Tuyau du BAS
    // Il part de la fin du trou et va jusqu'à 600 (bas de l'écran)
    SDL_FRect bottomPipe;
    bottomPipe.x = mX;
    bottomPipe.y = mGapY + (gapSize / 2); // Commence après le trou
    bottomPipe.w = width;
    bottomPipe.h = 600 - bottomPipe.y;    // Va jusqu'en bas
    SDL_RenderFillRect(renderer, &bottomPipe);
}

bool Pipe::IsOffScreen() {
    // Si le tuyau est complètement à gauche de l'écran (x < -largeur)
    return (mX + width < 0);
}