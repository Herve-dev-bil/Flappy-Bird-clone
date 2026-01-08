#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : mWindow(nullptr), mSDLRenderer(nullptr) {
}

Renderer::~Renderer() {
    Shutdown();
}

bool Renderer::Initialize() {
    // On initialise la vidéo
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL: %s", SDL_GetError());
        return false;
    }

    // Création fenêtre
    mWindow = SDL_CreateWindow("Flappy Bird Architecture", 800, 600, 0);
    if (!mWindow) return false;

    // Création moteur de rendu
    mSDLRenderer = SDL_CreateRenderer(mWindow, NULL);
    if (!mSDLRenderer) return false;

    return true;
}

void Renderer::BeginDraw() {
    // Couleur Bleu Ciel
    SDL_SetRenderDrawColor(mSDLRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mSDLRenderer);
}

void Renderer::EndDraw() {
    SDL_RenderPresent(mSDLRenderer);
}

void Renderer::DrawRect(const SDL_FRect* rect, float r, float g, float b, float a) {
    // Convertir les couleurs 0-1 en 0-255 si nécessaire, ou utiliser directement Uint8
    // Ici on suppose que vous passez 0-255.
    SDL_SetRenderDrawColor(mSDLRenderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
    SDL_RenderFillRect(mSDLRenderer, rect);
}

void Renderer::Shutdown() {
    if (mSDLRenderer) SDL_DestroyRenderer(mSDLRenderer);
    if (mWindow) SDL_DestroyWindow(mWindow);
    SDL_Quit();
}