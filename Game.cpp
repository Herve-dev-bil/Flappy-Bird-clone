#include "Game.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true) {
    SDL_Init(SDL_INIT_VIDEO);
    // Création fenêtre 800x600
    mWindow = SDL_CreateWindow("Projet 8 - Flappy Bird", 800, 600, 0);
    // Création du dessinateur (Renderer)
    mRenderer = SDL_CreateRenderer(mWindow, NULL);
}

Game::~Game() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::Run() {
    while (mIsRunning) {
        ProcessInput();
        Update();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Si on clique sur la croix ou appuie sur Echap
        if (event.type == SDL_EVENT_QUIT || 
           (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
            mIsRunning = false;
        }
    }
}

void Game::Update() {
    // La physique viendra ici 
}

void Game::GenerateOutput() {
    // 1. Couleur Bleu Ciel (R, G, B, Alpha)
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    
    // 2. Nettoyer l'écran avec cette couleur
    SDL_RenderClear(mRenderer);

    // 3. Afficher
    SDL_RenderPresent(mRenderer);
}