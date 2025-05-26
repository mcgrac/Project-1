#include"Mushroom.hpp"
#include"GameManager.hpp"

Mushroom::Mushroom(float x, float y, float width, float height, int id, int state, int typePower_) :BaseObject(x, y, width, height, id, state, typePower_) {

    mushroom = LoadTexture("resources/textures/mushroom.png"); // Replace with correct texture path
    popUp = LoadSound("resources/audio/PowerUp.wav");
}

Mushroom::~Mushroom() {
    UnloadTexture(mushroom);
    UnloadSound(popUp);
}

void Mushroom::throwPower() {

    PlaySound(popUp);
    emerging = true;
    emergedSoFar = 0.0f;
}

void Mushroom::update(vector<Entity*>& entity, float gravity) {
    float delta = GetFrameTime();

    if (emerging && !touched) {
        float move = emergeSpeed * delta * 60;
        hitbox.y -= move;
        emergedSoFar += move;
        if (emergedSoFar >= maxEmerge) {
            emerging = false;
            touched = true;
            velocity.x = initialSpeed; // Start moving right after emerging
        }
    }
    else if (!emerging && touched){
        updateRects();

        hitbox.x += velocity.x * delta;

        velocity.y += gravity * delta;
        if (velocity.y > terminalVelocityY) {
            velocity.y = terminalVelocityY;
        }

        hitbox.y += velocity.y * delta;

        handleCollision();
    }
}

void Mushroom::handleCollision() {
    const float push = 0.1f;

    for (Entity* ent : GameManager::getAllEntities()) {
        if (ent->getId() != 2) continue; // Only collide with blocks

        Rectangle block = ent->getHitbox();
        if (CheckCollisionRecs(getHitbox(), block)) {
            // Ground
            if (velocity.y > 0 && CheckCollisionPointRec(bottom, block)) {
                hitbox.y = block.y - hitbox.height;
                velocity.y = 0.0f;
            }
            // Ceiling
            else if (velocity.y < 0 && CheckCollisionPointRec(top, block)) {
                hitbox.y = block.y + block.height;
                velocity.y = 0.0f;
            }

            // Left
            if (velocity.x < 0 && CheckCollisionPointRec(left, block)) {
                hitbox.x = block.x + block.width + push;
                velocity.x *= -1;
            }
            // Right
            else if (velocity.x > 0 && CheckCollisionPointRec(right, block)) {
                hitbox.x = block.x - hitbox.width - push;
                velocity.x *= -1;
            }
        }
    }
}

void Mushroom::draw() {
    DrawTexture(mushroom, hitbox.x, hitbox.y, WHITE);
}

