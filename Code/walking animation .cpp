#include "Player.hpp"
#include <cstdio>
#include <vector>

using namespace std;

Player::Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_)
    : Entity(x, y, width, height, id, state),
    speed{ speedX, speedY },
    movementSpeed(movementSpeed_),
    isJumping(false),
    onGround(false),
    colliding(false),
    immunity(false),
    time(3.0f),
    frameCounter(0),
    currentFrame(0),
    frameSpeed(8),
    direction(direction_) {

    frameRec = { 0.0f, 0.0f, width, height };

    big_mario0 = LoadTexture("resources/walking_animation0.png");
    big_mario1 = LoadTexture("resources/walking_animation1.png");
    big_mario_jump0 = LoadTexture("resources/bmario_jump0.png");
    big_mario_jump1 = LoadTexture("resources/bmario_jump1.png");
}

void Player::draw() {
    frameCounter++;

    if (onGround) {
        if (frameCounter >= (60 / frameSpeed)) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame > 3) currentFrame = 0;
        }

        frameRec.x = (float)currentFrame * frameRec.width;
    }

    Texture2D currentTexture;
    if (direction == 0) {
        currentTexture = onGround ? big_mario0 : big_mario_jump0;
    }
    else {
        currentTexture = onGround ? big_mario1 : big_mario_jump1;
    }

    if (onGround) {
        DrawTextureRec(currentTexture, frameRec, { hitbox.x, hitbox.y }, WHITE);
    }
    else {
        DrawTexture(currentTexture, hitbox.x, hitbox.y, WHITE);
    }
}

void Player::jump(float jumpForce) {
    if (!isJumping) {
        speed.y = -jumpForce;
        isJumping = true;
    }
}

float Player::getTime() {
    return time;
}

void Player::changeDirection() {
    if (direction == 1) {
        direction = 0;
    }
    else if (direction == 0) {
        direction = 1;
    }
}

void Player::applyGravity(float gravity) {
    printf("Mario position: x->%f / y->%f\n", hitbox.x, hitbox.y);
    speed.y += gravity;
    hitbox.y += speed.y;
}

void Player::move(int direction) {
    if (direction == 1) {
        hitbox.x += movementSpeed;
    }
    else {
        hitbox.x -= movementSpeed;
    }
}

void Player::immunityVoid(Player& mario) {
    if (mario.immunity) {
        mario.time -= GetFrameTime();
        if (mario.time <= 0) {
            mario.immunity = false;
            mario.time = 3;
        }
    }
}

void Player::colisionsPlayer(vector<Entity*> e) {
    for (int i = 0; i < e.size(); ++i) {
        if (e[i]->id == 2 && CheckCollisionRecs(hitbox, e[i]->getHitbox())) {
            printf("colision con bloque\n");

            if (collidingBottom(e[i])) {
                speed.y = 0;
                hitbox.y = e[i]->getHitbox().y - hitbox.height;
                isJumping = false;
            }

            if (collidingAbove(e[i])) {
                hitbox.y = e[i]->getHitbox().y + e[i]->getHitbox().height;
                speed.y = 1.0f;
            }

            if (CheckCollisionPointRec(left, e[i]->getHitbox())) {
                hitbox.x = e[i]->getHitbox().x + e[i]->getHitbox().width;
            }

            if (CheckCollisionPointRec(right, e[i]->getHitbox())) {
                hitbox.x = e[i]->getHitbox().x - e[i]->getHitbox().width;
            }
        }

        if (CheckCollisionRecs(hitbox, e[i]->getHitbox()) && !immunity && e[i]->id == 1) {
            if (CheckCollisionPointRec(bottom, e[i]->getHitbox())) {
                printf("COLLISION GOOMBA CON LOS PIES\n");
                e[i]->state = 0;
                jump(8.0f);
            }
            else {
                printf("COLISION CON GOOMBA\n");
                state--;
                if (state == 0) {
                    // Mario muere
                }
                else {
                    immunity = true;
                }
            }
        }
    }
}
