#ifndef BIRD_H
#define BIRD_H

#include <SDL3/SDL.h>

class Bird {
public:
    // La Naissance
    Bird();
//fonction pour mouvement
    void Update(float deltaTime);
    //  L'Affichage
    void Draw(SDL_Renderer* renderer);

    //capacite saut
    void Jump();

private:
    //  Le Corps (Position et Taille)
   
    SDL_FRect mRect;
//variables physique
    float mVelocity;       // Vitesse actuelle (0 = arrêt, positif = descend)
    const float GRAVITY = 1500.0f;// Force de la chute
};


#endif