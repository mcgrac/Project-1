
#pragma once

#include "BaseObject.hpp"
#include "raylib.h"

// Fire Flower power-up: emerges from blocks and floats side-to-side
class Flower : public BaseObject {
public:
    // Constructor: x,y position, size, id, state, power-up type
    Flower(float x, float y, float width, float height, int id, int state, int typePower_);

    ~Flower() = default;

    // Load and unload shared assets (call once at startup/shutdown)
    static void LoadAssets();
    static void UnloadAssets();


    // Make the pickup sound available
    static Sound sPickupSound;

    // Pop the flower out of its block
    void throwPower() override;

    // Update logic: emerging or floating
    void update(float gravity) override;
    // Draw the flower
    void draw() override;

private:
    // Handle horizontal collisions to reverse direction
    void handleCollisionX();

    // Animation frames (2-frame pulse)
    static Texture2D sTex[2];
    // Spawn sound
    static Sound     sSndSpawn;

    // Floating direction: +1 = right, -1 = left
    int direction = 1;
    // Animation counters
    int frameCounter = 0;
    int currentFrame = 0;
    const int frameSpeed = 8;  // ticks per frame
    // Horizontal float speed after emerging
    static constexpr float floatSpeed = 30.0f;
};
