#include "Fireball.hpp"

#include <algorithm>    // for std::remove
#include <raylib.h>

// Static definitions
Texture2D Fireball::sTex;
Sound     Fireball::sSndLaunch;
Sound     Fireball::sSndHit;

void Fireball::LoadAssets() {
    sTex = LoadTexture("resources/textures/fireball1.png");
    sSndLaunch = LoadSound("resources/audio/ThrowFireball.wav");
    sSndHit = LoadSound("resources/audio/FireballHit.wav");
}

void Fireball::UnloadAssets() {
    UnloadTexture(sTex);
    UnloadSound(sSndLaunch);
    UnloadSound(sSndHit);
}

Fireball::Fireball(float x, float y, float width, float height, int direction)
    : Entity(x, y, width, height, /*id=*/4, /*state=*/1),
    velocity{ floatSpeed * direction, 0 }
{
    LoadAssets();
    // Play launch sound immediately
    PlaySound(sSndLaunch);

    // Prepare collision midpoints if needed
    updateRects();
}

Fireball::~Fireball() {
    UnloadAssets();
}

void Fireball::update(vector<Entity*>& entity, float gravity) {

    printf("UPDATE FIREBALLS\n");

    float dt = GetFrameTime();

    // Apply gravity to vertical velocity, clamped
    velocity.y += gravity * dt * 60;
    if (velocity.y > terminalVelocityY) velocity.y = terminalVelocityY;

    
    // Move fireball
    hitbox.x += velocity.x * dt;
    hitbox.y += velocity.y * dt;

    // Check for collisions (blocks/enemies)
    handleCollisions(entity);

    // Update midpoint helpers
    updateRects();
}

void Fireball::handleCollisions(vector<Entity*>& entity) {

    auto& entities = entity;

    for (auto it = entities.begin(); it != entities.end(); ++it) {
        Entity* e = *it;

        // 1) Enemy collision: kill Goomba
        if (e->getId() == 1 && CheckCollisionRecs(hitbox, e->getHitbox())) {
            if (Enemy* enemy = dynamic_cast<Enemy*>(e)) {
                enemy->decreaseState();
                if (enemy->getState() == 0) {

                    enemy->markForDelation();
                    //delete g;
                    //entities.erase(it);
                }
            }

            // Fireball also dies
            toDelete = true;
            alive = false;
            PlaySound(sSndHit);
            return;
        }

        // 2) Block collision: bounce or die
        if (e->getId() == 2 && CheckCollisionRecs(hitbox, e->getHitbox())) {
            Rectangle b = e->getHitbox();

            // Side collisions
            if (velocity.x > 0 && CheckCollisionPointRec(getRight(), b)) {
                if (bouncesLeft-- != 0) velocity.x *= -1;
                else { toDelete = true; PlaySound(sSndHit); return; }
            }
            else if (velocity.x < 0 && CheckCollisionPointRec(getLeft(), b)) {
                if (bouncesLeft-- != 0) velocity.x *= -1;
                else { toDelete = true; PlaySound(sSndHit); return; }
            }
            // Vertical collisions
            else if ((velocity.y > 0 && CheckCollisionPointRec(getBottom(), b)) ||
                (velocity.y < 0 && CheckCollisionPointRec(getTop(), b))) {
                if (bouncesLeft-- == 0) { toDelete = true; } //if bounces is 0 delete this
                velocity.y = -250.0f; //bounce
                //alive = false;
                PlaySound(sSndHit);
                return;
            }
        }
    }
}

void Fireball::draw() {

    DrawTexture(sTex, hitbox.x, hitbox.y, WHITE);

}
