#include "Bird.h"

#include "SDL_image.h" // Important pour IMG_LoadTexture


//=======================================================================================

Bird::Bird()
{

    // position depart definit
    mRect.x = 100.0f;
    mRect.y = 300.0f;

    mRect.w = 50.0f; // Largeur de l'image
    mRect.h = 35.0f; // Hauteur de l'image

    mVelocity = 0.0f; // depart->vitesse=0
}


//=======================================================================================

bool Bird::Initialize(SDL_Renderer *renderer)
{// On charge l'image originale (l'oiseau unique)
    mTexture = IMG_LoadTexture(renderer, "assets/images/flappyOld-removebg-preview (1).png");
    
    if (!mTexture)
    {
        SDL_Log("Erreur chargement Bird : %s", SDL_GetError());
        return false;
    }

    return true;
}

//=======================================================================================

void Bird::Jump()
{
    mVelocity = -500.0f; // inverse donc negatiif
}

//=======================================================================================


void Bird::Update(float deltaTime)
{
    mVelocity += GRAVITY * deltaTime;

    mRect.y += mVelocity * deltaTime;

}

//=======================================================================================


// affichage

void Bird::Draw(SDL_Renderer *renderer)
{
    if (mTexture)
    {
        // dessine la texture
        SDL_RenderTexture(renderer, mTexture, NULL, &mRect);
        SDL_FRect debugBox= GetHitbox();

        //Dessiner la hitbox en rouge, aide a visualiser le hitbox
     /*  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &debugBox);

         SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &mRect);*/
    }
    else
    {
        // par securite si l'image ne s'affiche pas
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        SDL_RenderFillRect(renderer, &mRect);
    }
}

//=======================================================================================

SDL_FRect Bird::GetHitbox()
{
    float paddingX = 8.0f; 
    float paddingY = 6.0f; 

    SDL_FRect hitbox;
    
    // On rétrécit le rectangle
    hitbox.x = mRect.x + paddingX;
    hitbox.y = mRect.y + paddingY;
    hitbox.w = mRect.w - (paddingX * 2);
    hitbox.h = mRect.h - (paddingY * 2);
    
    return hitbox;
}
//=======================================================================================
