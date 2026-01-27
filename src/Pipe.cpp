#include "Pipe.h"
#include <cstdlib> // Pour rand() (nombres aléatoires)

//=======================================================================================

Pipe::Pipe(float startX)
{
    mX = startX;

    // On choisit une hauteur de trou aléatoire
    // Le trou sera entre 150px et 450px de hauteur
    mGapY = 150.0f + (rand() % 300);

    mIsPassed = false; // Par défaut, le tuyau n'est pas encore passé
}

//=======================================================================================

void Pipe::Update(float deltaTime)
{
    // Le tuyau avance vers la gauche
    mX -= SPEED * deltaTime;
}

//=======================================================================================

void Pipe::Draw(SDL_Renderer *renderer, SDL_Texture *texture)
{
    // 1. Tuyau du HAUT (Retourné verticalement)
    SDL_FRect topRect = GetTopRect();

    if (texture)
    {
        // On utilise RenderTextureRotated pour faire le FLIP
        SDL_RenderTextureRotated(
            renderer,
            texture,
            NULL,             // Toute l'image source
            &topRect,         // Destination
            0.0,              // Pas de rotation d'angle
            NULL,             // Centre de rotation par défaut
            SDL_FLIP_VERTICAL // Tête en bas(flip)

        );
         //pour voir les hitbox des tuyau
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &topRect);
    }
    else
    {
        // Mode secours (Vert)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &topRect);
    }

    // 2. Tuyau du BAS (Normal)
    SDL_FRect bottomRect = GetBottomRect();

    if (texture)
    {
        SDL_RenderTexture(renderer, texture, NULL, &bottomRect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &bottomRect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bottomRect);
    }
}

//=======================================================================================

bool Pipe::IsOffScreen()
{
    // Si le tuyau est complètement à gauche de l'écran (x < -largeur)
    return (mX + WIDTH< 0);
}

// FONCTIONS DE COLLISION (Hitboxes)
SDL_FRect Pipe::GetTopRect()
{
    // Le tuyau du haut va de 0 jusqu'au début du trou
    return {mX, 0, WIDTH, mGapY - (GAP_SIZE / 2)};
}
SDL_FRect Pipe::GetBottomRect()
{
    // Le tuyau du bas commence après le trou et va jusqu'en bas (600)
    return {mX, mGapY + (GAP_SIZE / 2), WIDTH, 600.0f - (mGapY + (GAP_SIZE / 2))};
}
//=======================================================================================
