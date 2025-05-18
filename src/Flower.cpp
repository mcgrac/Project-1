#include "Flower.hpp"
#include "GameManager.hpp"
#include <cstdlib>

// Static asset definitions
Texture2D Flower::sTex[2];
Sound     Flower::sSndSpawn;
// Define the static
Sound Flower::sPickupSound;

void Flower::LoadAssets() {
    // Two-frame flower animation
    sTex[0] = LoadTexture("resources/textures/flower1.png");
    sTex[1] = LoadTexture("resources/textures/flower2.png");
    sSndSpawn = LoadSound("resources/audio/PowerUp.wav");
    sPickupSound = LoadSound("resources/audio/PowerUp.wav");  // your jingle
}

void Flower::UnloadAssets() {
    UnloadTexture(sTex[0]);
    UnloadTexture(sTex[1]);
    UnloadSound(sSndSpawn);
    UnloadSound(sPickupSound);
}

Flower::Flower(float x, float y, float width, float height,
    int id, int state, int typePower_)
    : BaseObject(x, y, width, height, id, state, typePower_) {

    LoadAssets();
    // Nothing else: emerging logic in BaseObject::throwPower()
}

Flower::~Flower() {

    UnloadAssets();
}

void Flower::throwPower() {
    // Start emerging animation
    emerging = true;
    emergedSoFar = 0.0f;

    PlaySound(sSndSpawn);
}

void Flower::update(float gravity) {
    float dt = GetFrameTime();
    if (emerging && !touched) {
        // Pop up from block
        float move = emergeSpeed * dt * 60.0f;
        hitbox.y -= move;
        emergedSoFar += move;
        if (emergedSoFar >= maxEmerge) {
            emerging = false;
            touched = true;
            updateRects();
        }
    }

}

void Flower::draw() {
    // Simple two-frame pulse animation
    frameCounter = (frameCounter + 1) % frameSpeed;
    if (frameCounter == 0) {
        currentFrame = (currentFrame + 1) % 2;
    }
    DrawTexture(
        sTex[currentFrame],
        (int)hitbox.x,
        (int)hitbox.y,
        WHITE
    );
}

