#ifndef BIRD_H
#define BIRD_H

#include <SDL3/SDL.h>

class Bird
{
public:
    // La Naissance
    Bird();

    // fonction pour mouvement
    void Update(float deltaTime);

    //  L'Affichage
    void Draw(SDL_Renderer *renderer);

    // capacite saut
    void Jump();

    bool Initialize(SDL_Renderer *renderer);

//accesseur au mRect(getter)
const SDL_FRect& GetRect() const { return mRect; }

private:
    // l'image de flappy
    SDL_Texture *mTexture;

    //  Le Corps (Position et Taille)
    SDL_FRect mRect;

    // variables physique
    float mVelocity;               // Vitesse actuelle (0 = arrêt, positif = descend)
    const float GRAVITY = 1500.0f; // Force de la chute
};

#endif