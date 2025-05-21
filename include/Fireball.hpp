#pragma once

#include "Entity.hpp"
#include "raylib.h"

// A fireball shot by Fire-Mario: moves horizontally, bounces once, destroys enemies on contact
class Fireball : public Entity {
public:
    // Load/unload shared assets (call once at startup/shutdown)
    static void LoadAssets();
    static void UnloadAssets();

    // Constructor: initial position, size, and horizontal direction (+1 right, –1 left)
    Fireball(float x, float y, float width, float height, int direction);

    ~Fireball();

    // Update motion and collisions each frame
    void update(vector<Entity*>& entity, float gravity) override;
    // Draw the fireball sprite
    void draw() override;

    // Returns whether this fireball is still active
    bool isAlive() const { return alive; }

private:
    // Handle collisions with blocks (bounce or die) and enemies
    void handleCollisions();

    // Shared texture & sounds
    static Texture2D sTex;
    static Sound     sSndLaunch;
    static Sound     sSndHit;

    // Movement constants
    static constexpr float floatSpeed = 20.0f;   // horizontal speed (px/sec)
    static constexpr float terminalVelocityY = 500.0f;   // max downward speed (px/sec)

    // Current velocity; gravity applies to y
    Vector2 velocity;

    // Has it hit something and should be removed?
    bool alive = true;

    // Maximum number of bounces allowed
    int bouncesLeft = 1;
};
