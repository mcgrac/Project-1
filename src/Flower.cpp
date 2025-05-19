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
    // Nothing else: emerging logic in BaseObject::throwPower()
}

void Flower::throwPower() {
    // Start emerging animation,  resets the pop-up distance.
    emerging = true;
    emergedSoFar = 0.0f;                                                                                                        
    // Initialize horizontal float once popped
    velocity.x = floatSpeed * direction;
    PlaySound(sSndSpawn);
}

void Flower::update(float gravity) {
    float dt = GetFrameTime();
    if (emerging) {
        // Pop up from block
        float move = emergeSpeed * dt * 60.0f;
        hitbox.y -= move;
        emergedSoFar += move;
        if (emergedSoFar >= maxEmerge) {
            emerging = false;
            // Begin floating side-to-side
            velocity.x = floatSpeed * direction;
        }
    }
    else {
        // Update collision midpoints
        updateRects();
        // Horizontal float
        hitbox.x += velocity.x * dt;
        // Bounce on block sides
        handleCollisionX();
    }
}

void Flower::handleCollisionX() {
    const float push = 0.1f;
    for (Entity* e : GameManager::getAllEntities()) {
        if (e->getId() != 2) continue; // only blocks
        Rectangle b = e->getHitbox();
        if (CheckCollisionRecs(hitbox, b)) {
            // Move right -> hit block on right
            if (velocity.x > 0 && CheckCollisionPointRec(right, b)) {
                hitbox.x = b.x - hitbox.width - push;
                direction = -1;
            }
            // Move left -> hit block on left
            else if (velocity.x < 0 && CheckCollisionPointRec(left, b)) {
                hitbox.x = b.x + b.width + push;
                direction = 1;
            }
            // Update velocity to match new direction
            velocity.x = floatSpeed * direction;
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
