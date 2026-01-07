#ifndef BIRD_H
#define BIRD_H

#include <SDL3/SDL.h>

// On dit à l'ordinateur que la classe "Renderer" existe (Forward Declaration)
class Renderer; 

class Bird {
public:
    Bird();
    void Update(float deltaTime);

    // CHANGEMENT ICI : On prend votre Renderer, pas celui de SDL
    void Draw(Renderer* renderer);

private:
    SDL_FRect mRect;
    float mVelocity;
    const float GRAVITY = 1000.0f;
};

#endif