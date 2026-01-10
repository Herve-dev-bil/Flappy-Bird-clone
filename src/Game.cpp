#include "Game.h"

// --- LE CONSTRUCTEUR (Naissance) ---
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mBird(nullptr)
{
   
    // 1. On démarre le système vidéo de SDL
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("Flappy Bird", 800, 600, 0);

    // NULL = Laisse SDL choisir le meilleur pilote (DirectX etc.)
    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    mBird = new Bird();

    if (!mBird->Initialize(mRenderer))
    {
        SDL_Log("Attention : L'oiseau n'a pas pu charger son image !");
    }

     //initialise le chronometre a 0
    mPipeSpawnTimer = 0.0f;

}

Game::~Game()
{

    delete mBird;
    // On détruit dans l'ordre inverse de la création
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit(); // On éteint SDL
}

void Game::Update(float deltaTime)
{
    // l'oiseau Calcule sa nouvelle position selon le temps écoulé"
    mBird->Update(deltaTime);
    mPipeSpawnTimer += deltaTime;
    if (mPipeSpawnTimer >= 1.5f)
    { // Tous les 1.5 secondes
        // On crée un nouveau tuyau à droite de l'écran (800px)
        mPipes.push_back(new Pipe(800.0f));
        mPipeSpawnTimer = 0.0f; // On remet le chrono à 0
    }

    // 2. MISE À JOUR DES TUYAUX
    // On utilise une boucle spéciale pour parcourir la liste
    for (int i = 0; i < mPipes.size(); i++)
    {
        mPipes[i]->Update(deltaTime);

        // Si le tuyau est sorti de l'écran
        if (mPipes[i]->IsOffScreen())
        {
            delete mPipes[i];                 // On supprime l'objet en mémoire
            mPipes.erase(mPipes.begin() + i); // On l'enlève de la liste
            i--;                              // On recule l'index car la liste a rétréci
        }
    }
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
        }
        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_SPACE)
            {
                if (!event.key.repeat)
                {
                    mBird->Jump();
                }
            }
        }
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);

    // DESSINER LES TUYAUX
    for (auto pipe : mPipes)
    {
        pipe->Draw(mRenderer);
    }
    SDL_RenderClear(mRenderer);
    mBird->Draw(mRenderer);

    SDL_RenderPresent(mRenderer);
}