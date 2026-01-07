#include "Bird.h"
#include "Renderer.h" // <--- Important pour connaître DrawRect

Bird::Bird() {
    mRect.x = 100.0f;
    mRect.y = 300.0f;
    mRect.w = 30.0f;
    mRect.h = 30.0f;
    mVelocity = 0.0f;
}

void Bird::Update(float deltaTime) {
    mVelocity += GRAVITY * deltaTime;
    mRect.y += mVelocity * deltaTime;
}

void Bird::Draw(Renderer* renderer) {
    // Au lieu de faire du code SDL compliqué ici, on utilise votre outil simple :
    // (Rouge=255, Vert=255, Bleu=0 -> Jaune)
    renderer->DrawRect(&mRect, 255, 255, 0, 255);
}