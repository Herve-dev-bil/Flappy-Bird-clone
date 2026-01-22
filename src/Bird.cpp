#include "Bird.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Bird::Bird()
{

    // position depart definit
    mRect.x = 100.0f;
    mRect.y = 300.0f;

    mRect.w = 68.0f; // Largeur de l'image
    mRect.h = 48.0f; // Hauteur de l'image

    mVelocity = 0.0f; // depart->vitesse=0
}

bool Bird::Initialize(SDL_Renderer *renderer)
{
    // Charger l'image avec STB (Supporte PNG, JPG, etc.)
    int width, height, channels;
    // On force 4 canaux (Rouge, Vert, Bleu, Alpha/Transparence)
    unsigned char *data = stbi_load("assets/images/flappyOld-removebg-preview (1).png", &width, &height, &channels, 4);

    if (!data)
    {
        SDL_Log("Erreur chargement image (STB) : %s", stbi_failure_reason());
        return false;
    }

    // SDL3 a besoin de savoir : Largeur, Hauteur, Format, Données, et Pitch (largeur * 4 octets)
    SDL_Surface *surface = SDL_CreateSurfaceFrom(
        width,
        height,
        SDL_PIXELFORMAT_RGBA32,
        data,
        width * 4);

    if (!surface)
    {
        SDL_Log("Erreur création surface : %s", SDL_GetError());
        stbi_image_free(data); // Important : Nettoyer la mémoire de STB
        return false;
    }

    // 3. Créer la Texture GPU
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);

    // 4. Nettoyage
    SDL_DestroySurface(surface);
    stbi_image_free(data); // On libère la RAM utilisée par STB

    return mTexture != nullptr;
}

void Bird::Jump()
{
    mVelocity = -500.0f; // inverse donc negatiif
}

void Bird::Update(float deltaTime)
{
    mVelocity += GRAVITY * deltaTime;

    mRect.y += mVelocity * deltaTime;

}

// affichage

void Bird::Draw(SDL_Renderer *renderer)
{
    if (mTexture)
    {
        // dessine la texture
        SDL_RenderTexture(renderer, mTexture, NULL, &mRect);
        SDL_FRect debugBox= GetHitbox();

        //Dessiner la hitbox en rouge, aide a visualiser le hitbox
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &debugBox);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderRect(renderer, &mRect);
    }
    else
    {
        // par securite si l'image ne s'affiche pas
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        SDL_RenderFillRect(renderer, &mRect);
    }
}
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