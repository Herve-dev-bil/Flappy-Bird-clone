#include "Game.h"


// --- LE CONSTRUCTEUR (Naissance) ---
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mBird(nullptr){
    // 1. On démarre le système vidéo de SDL
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("Flappy Bird", 800, 600, 0);

    // NULL = Laisse SDL choisir le meilleur pilote (DirectX etc.)
    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    mBird = new Bird();

    if (!mBird->Initialize(mRenderer)) {
        SDL_Log("Attention : L'oiseau n'a pas pu charger son image !");
    }

}

Game::~Game()
{

    delete mBird;
    // On détruit dans l'ordre inverse de la création
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit(); // On éteint SDL
}

void Game::Update(float deltaTime) {
    // l'oiseau Calcule sa nouvelle position selon le temps écoulé"
    mBird->Update(deltaTime);
}
void Game::Run()
{

    Uint64 lastTime = SDL_GetTicks();

    while (mIsRunning)
    {

        Uint64 currentTime = SDL_GetTicks();
        // difference du temps
        float deltaTime = (currentTime - lastTime) / 1000.0f;

        // mise a jour de l'heure
        lastTime = currentTime;

        ProcessInput();
        Update(deltaTime);
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_EVENT_QUIT)
        {
            mIsRunning = false;

        } else if(event.type == SDL_EVENT_KEY_DOWN){
            if(event.key.key == SDLK_SPACE){
                if(!event.key.repeat){
                    mBird->Jump();
                }
            }

        }
    }
}


void Game::GenerateOutput(){
SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);

SDL_RenderClear(mRenderer);
mBird->Draw(mRenderer);

SDL_RenderPresent(mRenderer);
}