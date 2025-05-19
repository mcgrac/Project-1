#include "Goomba.hpp"
#include "raylib.h"

Goomba::Goomba(float x, float y, float width, float height, int id, int state, float movementSpeed_, int direction_)
    : Enemy(x, y, width, height, id, state), movementSpeed(movementSpeed_), direction(direction_) {

#pragma region TEXTURES
    goomba1 = LoadTexture("resources/textures/Goomba1.png");
    goomba2 = LoadTexture("resources/textures/Goomba2.png");
    goombaDeadT = LoadTexture("resources/textures/Goomba3.png");
#pragma endregion

#pragma region SOUNDS
    //sounds
    goombaDieS = LoadSound("resources/audio/smb_stomp.wav");
#pragma endregion

    updateRects();
}

Goomba::~Goomba() { //destructor

#pragma region TEXTURES
    UnloadTexture(goomba1);
    UnloadTexture(goomba2);
    UnloadTexture(goombaDeadT);
#pragma endregion
}


float Goomba::getMovementSpeed() {
    return movementSpeed;
}


void Goomba::draw() {

    //printf("Drawing goomba. Position x: %f|position y: %f\n", hitbox.x, hitbox.y);

    frameCounter++;

    //animation
    if (frameCounter >= (60 / frameSpeed) && state !=0) {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame > 1) currentFrame = 0;
    }

    if (state == 0) { //gomba is dead

        DrawTexture(goombaDeadT, hitbox.x, hitbox.y, WHITE);
        //die();
    }
    else {

        if (currentFrame == 0) {
            DrawTexture(goomba1, hitbox.x, hitbox.y, WHITE);
        }
        else {
            DrawTexture(goomba2, hitbox.x, hitbox.y, WHITE);
        }
    }
}

void Goomba::update(vector<Entity*>& entity, float gravity) {
    if (state == 0) {
        deathTimer += GetFrameTime();
        if (deathTimer >= 2.0f) {
            markedForDeletion = true;
        }
    }
    else {
        moveGoomba(entity, gravity);
        collisionGoomba(entity);

        if (touched) {
            die(entity);
        }
    }
}


void Goomba::die(vector<Entity*>& entity) {
    if (state != 0) {
        state = 0; // dead
        PlaySound(goombaDieS);
        deathTimer = 0.0f;
    }
}


void Goomba::moveGoomba(vector<Entity*>& entity, float gravity) {

    float delta = GetFrameTime();

    // gravity
    hitbox.y += gravity * delta * 5;

    // lateral movement
    if (direction == 1) {
        hitbox.x += (movementSpeed - 4) * delta;
    }
    else {
        hitbox.x -= (movementSpeed - 4) * delta;
    }
    
    collisionGoomba(entity);
}

void Goomba::collisionGoomba(vector<Entity*>& entity) {

    for (int i = 0; i < entity.size(); ++i) {
        if (entity[i]->getId() == 2 && CheckCollisionRecs(hitbox, entity[i]->getHitbox())) { // block
            if (CheckCollisionPointRec(bottom, entity[i]->getHitbox())) { //collision with the floor
                hitbox.y = entity[i]->getHitbox().y - hitbox.height;
            }

            if (CheckCollisionPointRec(right, entity[i]->getHitbox()) && direction == 1) { //collision right side
                direction = -1;
            }

            if (CheckCollisionPointRec(left, entity[i]->getHitbox()) && direction == -1) { //collision left side
                direction = 1;
            }
        }
    }
}

