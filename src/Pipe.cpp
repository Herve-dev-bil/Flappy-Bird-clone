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
    topPipe.h = mGapY - (GAP_SIZE / 2); // S'arrête au début du trou
    SDL_RenderFillRect(renderer, &topPipe);

    // 2. Tuyau du BAS
    // Il part de la fin du trou et va jusqu'à 600 (bas de l'écran)
    SDL_FRect bottomPipe;
    bottomPipe.x = mX;
    bottomPipe.y = mGapY + (GAP_SIZE/ 2); // Commence après le trou
    bottomPipe.w = width;
    bottomPipe.h = 600 - bottomPipe.y;    // Va jusqu'en bas
    SDL_RenderFillRect(renderer, &bottomPipe);
}

bool Pipe::IsOffScreen() {
    // Si le tuyau est complètement à gauche de l'écran (x < -largeur)
    return (mX + width < 0);
}

//FONCTIONS DE COLLISION (Hitboxes)
SDL_FRect Pipe::GetTopRect() {
    // Le tuyau du haut va de 0 jusqu'au début du trou
    return {mX, 0, width, mGapY - (GAP_SIZE / 2)};
}
SDL_FRect Pipe::GetBottomRect() {
    // Le tuyau du bas commence après le trou et va jusqu'en bas (600)
    return {mX, mGapY + (GAP_SIZE / 2), width, 600.0f - (mGapY + (GAP_SIZE / 2))};
}