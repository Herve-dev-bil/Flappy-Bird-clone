#include "Bird.h"
#include "Renderer.h" // <--- Important pour connaître DrawRect

Bird::Bird() {

    //position depart definit
    mRect.x = 100.0f;
    mRect.y = 300.0f;
    //largeur, hauteur
    mRect.w = 30.0f;//petit carre 
    mRect.h = 30.0f;
}
//affichage


void Bird::Draw(SDL_Renderer* renderer) {

SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

   SDL_RenderFillRect(renderer, &mRect);
}