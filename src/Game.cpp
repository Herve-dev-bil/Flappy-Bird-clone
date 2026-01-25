#include "Game.h"
#include "SDL_image.h"
#include <iostream>

//=======================================================================================

SDL_Texture *Game::LoadTexture(const char *fileName)
{
    SDL_Texture *tex = IMG_LoadTexture(mRenderer, fileName);
    if (!tex)
    {
        SDL_Log("Erreur chargement texture %s : %s", fileName, SDL_GetError());
    }
    return tex;
}

//=======================================================================================
// --- LE CONSTRUCTEUR (Naissance) ---
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mBird(nullptr), game_paused(false)
{

    // 1. On démarre le système vidéo de SDL
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("Flappy Bird", 800, 600, 0);

    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    mBird = new Bird();

    if (!mBird->Initialize(mRenderer))
    {
        SDL_Log("Attention : L'oiseau n'a pas pu charger son image !");
    }

    // 4. On charge le décor (Ciel et Sol)
    mTexBackground = LoadTexture("assets/images/world1-removebg-preview (1).png");
    mTexGround = LoadTexture("assets/images/flappy_ground.png");
    mTexPipe = LoadTexture("assets/images/green_pipe-removebg-preview (1).png");
    mGroundX = 0.0f;

    // initialise le chronometre a 0
    mPipeSpawnTimer = 0.0f;
}

//=======================================================================================

Game::~Game()
{

    delete mBird;

    // 2. Nettoyage des tuyaux restants
    for (auto pipe : mPipes)
    {
        delete pipe;
    }
    mPipes.clear();

    // 3. Nettoyage des textures
    if (mTexBackground)
        SDL_DestroyTexture(mTexBackground);
    if (mTexGround)
        SDL_DestroyTexture(mTexGround);
    if (mTexPipe)
        SDL_DestroyTexture(mTexPipe);

    // On détruit dans l'ordre inverse de la création
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit(); // On éteint SDL
}

void Game::Update(float deltaTime)
{
    //1) l'oiseau Calcule sa nouvelle position selon le temps écoulé"
    mBird->Update(deltaTime);

    // 2) Collision Oiseau vs Sol
    SDL_FRect birdHitbox = mBird->GetHitbox();
    //regarde si le bas du hitbox touche le sol
    if (birdHitbox.y + birdHitbox.h >= 500.0f)
    {
        SDL_Log("MORT : Touché le sol !");
       game_paused = false;
    }

    // 3) Défilement du Sol
    mGroundX -= 200.0f * deltaTime;
    if (mGroundX <= -800.0f)
        mGroundX = 0.0f;

        //4)[gestion des Tuyaux]

    mPipeSpawnTimer += deltaTime;
    if (mPipeSpawnTimer >= 1.5f)
    { /* Tous les 1.5 secondes
         On crée un nouveau tuyau à droite de l'écran (800px)*/
        mPipes.push_back(new Pipe(800.0f));
        mPipeSpawnTimer = 0.0f; // On remet le chrono à 0
    }

    // MISE À JOUR DES TUYAUX
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
            continue;
        }

        //5) Score
        // Si le tuyau dépasse l'oiseau (X < 100) et n'est pas encore compté
        if (mPipes[i]->GetX() + 60.0f < 100.0f && !mPipes[i]->IsPassed())
        {
            mScore++;//augmente score par 1
            mPipes[i]->SetPassed();//definir le tuyau comme deja ete passee

            // Mise à jour du titre
            char titleBuffer[64];
            sprintf(titleBuffer, "Flappy Bird - Score: %d", mScore);
            SDL_SetWindowTitle(mWindow, titleBuffer);
        }

        SDL_FRect rTop = mPipes[i]->GetTopRect();
        SDL_FRect rBottom = mPipes[i]->GetBottomRect();

        SDL_FRect birdHitbox = mBird->GetHitbox();

        // Vérifie si l'oiseau touche le haut OU le bas du tuyau
        if (SDL_HasRectIntersectionFloat(&birdHitbox, &rTop) ||
            SDL_HasRectIntersectionFloat(&birdHitbox, &rBottom))
        {
            SDL_Log("MORT : Collision Tuyau !");
           game_paused = false;
        }
    }
}

//=======================================================================================
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
        if (!game_paused){
        Update(deltaTime);
        }
        GenerateOutput();
        
    }
}

//=======================================================================================
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

//=======================================================================================

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 135, 206, 235, 255);
    SDL_RenderClear(mRenderer);

    // Dessiner le fond (Image)
    if (mTexBackground)
    {
        SDL_RenderTexture(mRenderer, mTexBackground, NULL, NULL);
    }

    // Dessiner les Tuyaux
    for (auto pipe : mPipes)
    {
        pipe->Draw(mRenderer, mTexPipe);
    }

    // Dessiner le Sol (qui défile)
    if (mTexGround)
    {
        SDL_FRect r1 = {mGroundX, 500, 800, 100};
        SDL_RenderTexture(mRenderer, mTexGround, NULL, &r1);

        SDL_FRect r2 = {mGroundX + 800, 500, 800, 100};
        SDL_RenderTexture(mRenderer, mTexGround, NULL, &r2);
    }

    //  dessine l'oiseau
    mBird->Draw(mRenderer);

    // 4. On affiche le tout
    SDL_RenderPresent(mRenderer);
}