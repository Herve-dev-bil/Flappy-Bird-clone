#ifndef BIRD_H
#define BIRD_H

#include <SDL3/SDL.h>

class Bird {
public:
    // La Naissance
    Bird();

    //  L'Affichage
    void Draw(SDL_Renderer* renderer);

private:
    //  Le Corps (Position et Taille)
   
    SDL_FRect mRect;
};

#endif