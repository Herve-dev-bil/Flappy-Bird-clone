#include "Game.h"
#include "SDL_image.h"
#include <iostream>

// pour avoir le droit de manipuler des fichiers
#include <fstream>

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
Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mBird(nullptr)
{

    // 1. On démarre le système vidéo de SDL
    SDL_Init(SDL_INIT_VIDEO);

    mWindow = SDL_CreateWindow("Flappy Bird", 800, 600, 0);

    mRenderer = SDL_CreateRenderer(mWindow, NULL);

    mBird = new Bird();//Alloue la mémoire pour l'oiseau (dans le Heap) 

    if (!mBird->Initialize(mRenderer))
    {
        SDL_Log("Attention : L'oiseau n'a pas pu charger son image !");
    }

    // 4. On charge le décor (Ciel et Sol)
    mTexBackground = LoadTexture("assets/images/world1-removebg-preview (1).png");
    mTexGround = LoadTexture("assets/images/flappy_ground.png");
    mTexPipe = LoadTexture("assets/images/pipe-removebg-preview - Copy.png");
    mGroundX = 0.0f;

    // initialise le chronometre a 0
    mPipeSpawnTimer = 0.0f;

    mScore = 0;

    mState = STATE_MENU; // On commence sur le menu
    LoadHighScore();
    mUI.Init(mWindow, mRenderer);
}

//=======================================================================================

Game::~Game()
{
    mUI.Shutdown();
    delete mBird;//: Libère la mémoire de l'oiseau

    // 2. Nettoyage des tuyaux restants
    for (auto pipe : mPipes)
    {
        delete pipe;
    }
    mPipes.clear();

    // 3. Nettoyage des textures
    //Vide la mémoire de la carte graphique
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
        Update(deltaTime);
        GenerateOutput();
    }
}

//=======================================================================================

void Game::Update(float deltaTime)
{

    if (mState != STATE_PLAYING)
    {
        return;
    }
    // 1) l'oiseau Calcule sa nouvelle position selon le temps écoulé"
    mBird->Update(deltaTime);

    // 2) Collision Oiseau vs Sol
    SDL_FRect birdHitbox = mBird->GetHitbox();
    // regarde si le bas du hitbox touche le sol
    if (birdHitbox.y + birdHitbox.h >= 500.0f)
    {
        SDL_Log("MORT : Touché le sol !");
        mState = STATE_GAME_OVER;
        if (mScore > mHighScore)
        {
            mHighScore = mScore; // On met à jour la mémoire
            SaveHighScore();     // On écrit sur le disque dur immédiatement
            SDL_Log("Nouveau Record Sauvegardé !");
        }
    }

    // 3) Défilement du Sol
    mGroundX -= 200.0f * deltaTime;
    if (mGroundX <= -800.0f)
        mGroundX = 0.0f;

    // 4)[gestion des Tuyaux]

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

        // 5) Score
        //  Si le tuyau dépasse l'oiseau (X < 100) et n'est pas encore compté
        if (mPipes[i]->GetX() + 60.0f < 100.0f && !mPipes[i]->IsPassed())
        {
            mScore++;               // augmente score par 1
            mPipes[i]->SetPassed(); // definir le tuyau comme deja ete passee

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
            mState = STATE_GAME_OVER;

            if (mScore > mHighScore)
            {
                mHighScore = mScore; // On met à jour la mémoire
                SaveHighScore();     // On écrit sur le disque dur immédiatement
                SDL_Log("Nouveau Record Sauvegardé !");
            }
        }
    }
}

//=======================================================================================

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // On délègue à l'UI
        mUI.ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT)
        {
            mIsRunning = false;
        }

        else if (event.type == SDL_EVENT_KEY_DOWN)
        {
            // ceci empêche de sauter si on est en train de cliquer sur une fenêtre ImGui
           
                if (event.key.key == SDLK_SPACE && !event.key.repeat)
                {
                    // MACHINE A ÉTATS DES ENTRÉES
                    switch (mState)
                    {
                    case STATE_MENU:
                        RestartGame(); // Commence le jeu (même logique que restart)
                         mBird->Jump(); 
                        break;

                    case STATE_PLAYING:
                        mBird->Jump(); // Saute
                        break;

                    case STATE_GAME_OVER:
                    // Si MORT -> On recommence
                        RestartGame(); // Recommence
                        break;
                    }
                }
            }
        }
    };



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

    // Appel de la fonction Draw de l'UI
    bool startGame = false;
    bool restart = false;
    bool quit = false;

    // On passe mState à l'UI
    mUI.Draw(mRenderer, mState, mScore, mHighScore, startGame, restart, quit);

    // Actions des boutons
    if (startGame)
        RestartGame(); // Le bouton "Jouer" du menu lance le jeu
    if (restart)
        RestartGame(); // Le bouton "Recommencer" relance
    if (quit)
        mIsRunning = false;

    // 4. On affiche le tout
    SDL_RenderPresent(mRenderer);
}

//=======================================================================================

void Game::LoadHighScore()
{
    // On essaie d'ouvrir le fichier "highscore.txt" en lecture (input)
    std::ifstream file("highscore.txt");

    if (file.is_open())
    {
        file >> mHighScore; // On lit le nombre dans le fichier
        file.close();
    }
    else
    {
        // Si le fichier n'existe pas (première fois qu'on joue), le record est 0
        mHighScore = 0;
    }
}
//=======================================================================================


void Game::SaveHighScore()
{
    // On ouvre le fichier en écriture (output)
    // Cela écrase l'ancien contenu pour mettre le nouveau
    std::ofstream file("highscore.txt");

    if (file.is_open())
    {
        file << mHighScore; // On écrit le record dedans
        file.close();
    }
}
//=======================================================================================

void Game::RestartGame()
{
    // 1. On remet l'oiseau au début
    delete mBird;                 // On supprime l'ancien (mort)
    mBird = new Bird();           // On en crée un tout neuf
    mBird->Initialize(mRenderer); // On recharge son image

    // 2. On supprime tous les tuyaux actuels
    for (auto pipe : mPipes)
    {
        delete pipe;
    }
    mPipes.clear(); // La liste redevient vide

    // 3. On reset les timers
    mPipeSpawnTimer = 0.0f;

    // passe l'état à "PLAYING"
    mState = STATE_PLAYING;

    // 4. Petit cadeau : un tuyau facile au début
    mPipes.push_back(new Pipe(400.0f));

    mScore = 0;
    // Reset du titre de la fenêtre
    SDL_SetWindowTitle(mWindow, "Flappy Bird - Score: 0");

    mScore = 0;
    SDL_Log("Jeu redémarré !");
}
//=======================================================================================
