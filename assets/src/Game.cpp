#include "Game.h"
#include <SDL3/SDL.h> // Juste pour SDL_GetTicks et les Events

Game::Game() : mRenderer(nullptr), mBird(nullptr), mIsRunning(true) {
    // On crée les instances
    mRenderer = new Renderer();
    mBird = new Bird();
}

Game::~Game() {
    // On nettoie dans l'ordre inverse
    mRenderer->Shutdown(); // Fermer SDL
    delete mBird;
    delete mRenderer;
}

bool Game::Initialize() {
    // On demande au Renderer de s'initialiser (Fenêtre + SDL)
    if (!mRenderer->Initialize()) {
        return false;
    }
    return true;
}

void Game::Run() {
    // IMPORTANT : On doit initialiser avant de lancer la boucle !
    if (!Initialize()) {
        return;
    }

    Uint64 lastTicks = SDL_GetTicks();

    while (mIsRunning) {
        Uint64 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        ProcessInput();
        Update(deltaTime);
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            mIsRunning = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_ESCAPE) {
                mIsRunning = false;
            }
        }
    }
}

void Game::Update(float deltaTime) {
    mBird->Update(deltaTime);
}

void Game::GenerateOutput() {
    // Regardez comme c'est propre grâce à votre architecture :
    
    mRenderer->BeginDraw();       // 1. Effacer (Fond bleu)
    
    mBird->Draw(mRenderer);       // 2. Dessiner l'oiseau
    
    mRenderer->EndDraw();         // 3. Afficher
}