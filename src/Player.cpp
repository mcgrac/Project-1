#include "Player.hpp"
#include <cstdio>
#include<vector>
#include "SurpriseBlock.hpp"

using namespace std;

Player::Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_)
    : Entity(x, y, width, height, id, state),
    speed{ speedX, speedY },
    movementSpeed(movementSpeed_),
    isJumping(false),
    onGround(false),
    colliding(false),
    immunity(false),
    isWalking(false),
    time(3.0f),
    frameCounter(0),
    currentFrame(0),
    timer(0),
    frameSpeed(0.1f),
    direction(direction_){

    //textures
    //littleMarioR = LoadTexture("resources/mario1.png");
    //littleMarioL = LoadTexture("resources/Lmario1.png");
    //bMarioWalkLeft = LoadTexture("resources/walking_animation0.png");
    //bMarioWalkRight = LoadTexture("resources/walking_animation1.png");
#pragma region TEXTURES
#pragma region LITTLE MARIO

    walkRight[0] = LoadTexture("resources/textures/mario1.png");
    walkRight[1] = LoadTexture("resources/textures/mario2.png");
    walkRight[2] = LoadTexture("resources/textures/mario3.png");
    walkRight[3] = LoadTexture("resources/textures/mario4.png");

    //lMarioR1 = LoadTexture("resources/mario1.png");
    //lMarioR2 = LoadTexture("resources/mario2.png");
    //lMarioR3 = LoadTexture("resources/mario3.png");
    //lMarioR4 = LoadTexture("resources/mario4.png");

    walkLeft[0] = LoadTexture("resources/textures/Lmario1.png");
    walkLeft[1] = LoadTexture("resources/textures/Lmario2.png");
    walkLeft[2] = LoadTexture("resources/textures/Lmario3.png");
    walkLeft[3] = LoadTexture("resources/textures/Lmario4.png");

    //lMarioL1 = LoadTexture("resources/Lmario1.png");
    //lMarioL2 = LoadTexture("resources/Lmario2.png");
    //lMarioL3 = LoadTexture("resources/Lmario3.png");
    //lMarioL4 = LoadTexture("resources/Lmario4.png");

    jumplMarioL = LoadTexture("resources/textures/Lmario5.png");
    jumplMarioR = LoadTexture("resources/textures/mario5.png");
#pragma endregion

#pragma region BIG MARIO
    bMarioR1 = LoadTexture("resources/textures/bmario1.png");
    bMarioR2 = LoadTexture("resources/textures/bmario2.png");
    bMarioR3 = LoadTexture("resources/textures/bmario3.png");
    bMarioR4 = LoadTexture("resources/textures/bmario4.png");

    bMarioL1 = LoadTexture("resources/textures/Lbmario1.png");
    bMarioL2 = LoadTexture("resources/textures/Lbmario2.png");
    bMarioL3 = LoadTexture("resources/textures/Lbmario3.png");
    bMarioL4 = LoadTexture("resources/textures/Lbmario4.png");

    jumpbMarioL = LoadTexture("resources/textures/Lbmario5.png");
    jumpbMarioR = LoadTexture("resources/textures/bmario5.png");
#pragma endregion
#pragma endregion


    //bMarioR1 = LoadTexture("resources/bmario1.png");
    //bMarioR2 = LoadTexture("resources/bmario2.png");
    //bMarioR3 = LoadTexture("resources/bmario3.png");
    //bMarioR4 = LoadTexture("resources/bmario4.png");

    //bMarioL1 = LoadTexture("resources/Lbmario1.png");
    //bMarioL2 = LoadTexture("resources/Lbmario2.png");
    //bMarioL3 = LoadTexture("resources/Lbmario3.png");
    //bMarioL4 = LoadTexture("resources/Lbmario4.png");

    //jumpbMarioL = LoadTexture("resources/Lbmario5.png");
    //jumpbMarioR = LoadTexture("resources/bmario5.png");

    //sounds
    jumpSound = LoadSound("resources/audio/jumpSmall.wav");
    //SetSoundVolume(jumpSound, 1.0f); // Set proper volume
    jumpGoombaS = LoadSound("resources/audio/smb_stomp.wav");

    updateRects();
}

Player::~Player() {

    UnloadTexture(lMarioR1);
    UnloadTexture(lMarioR2);
    UnloadTexture(lMarioR3);
    UnloadTexture(lMarioR4);

    UnloadTexture(lMarioL1);
    UnloadTexture(lMarioL2);
    UnloadTexture(lMarioL3);
    UnloadTexture(lMarioL4);

    UnloadTexture(jumplMarioL);
    UnloadTexture(jumplMarioR);

    UnloadTexture(bMarioR1);
    UnloadTexture(bMarioR2);
    UnloadTexture(bMarioR3);
    UnloadTexture(bMarioR4);

    UnloadTexture(bMarioL1);
    UnloadTexture(bMarioL2);
    UnloadTexture(bMarioL3);
    UnloadTexture(bMarioL4);

    UnloadTexture(jumpbMarioL);
    UnloadTexture(jumpbMarioR);
    //UnloadTexture(littleMarioR);
    //UnloadTexture(littleMarioL);

    UnloadSound(jumpSound);
    UnloadSound(jumpGoombaS);
}

void Player::isWalkingTrue() {
    isWalking = true;
}
void Player::isWalkingFalse() {
    isWalking = false;
}
void Player::draw() {

    if (isWalking) {
        timer += GetFrameTime();
    }


    if (timer >= frameSpeed) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4; // Avanza entre 0 y 3
    }

    Vector2 position = { hitbox.x, hitbox.y };
    if (state == 1) {

        if (!isJumping) {
            if (direction == 1) {

                if (isWalking) {
                    // Derecha
                    DrawTexture(walkRight[currentFrame], position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(walkRight[0], position.x, position.y, WHITE);
                }

            }
            else {
                if (isWalking) {
                    // Izquierda
                    DrawTexture(walkLeft[currentFrame], position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(walkLeft[0], position.x, position.y, WHITE);
                }

            }
        }
        else {
            // Saltando: usar sprite estático de salto
            if (direction == 1) {
                DrawTexture(jumplMarioR, position.x, position.y, WHITE);
            }
            else {
                DrawTexture(jumplMarioL, position.x, position.y, WHITE);
            }
        }
    }
}

void Player::jump(float jumpForce) {
    if (!isJumping || !colliding) {
        speed.y = -jumpForce;
        isJumping = true;
    }

    //InitAudioDevice();
    if (!IsSoundPlaying(jumpSound) && !IsSoundPlaying(jumpGoombaS)) {

        PlaySound(jumpSound);
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

    //Apply gravity
    speed.y += gravity;
    hitbox.y += speed.y;
}
void Player::move(int direction, float cameraX) {
    float nextX = hitbox.x;

    if (direction == 1) {
        nextX += movementSpeed;
    }
    else {
        nextX -= movementSpeed;
    }

    float leftLimit = cameraX - 512.0f / 2.0f; // left side visible of the screen

    if (nextX >= leftLimit) {
        hitbox.x = nextX;
    }
    else {
        hitbox.x = leftLimit; // blocks mario from going ouside this limit
    }
}

void Player::immunityVoid() {
    if (immunity) {
        time -= GetFrameTime();
        if (time <= 0) {
            immunity = false;
            time = 3;
        }
    }
}

void Player::colisionsPlayer(vector<Entity*>& e) {

    for (auto it = e.begin(); it != e.end(); ) {
        Entity* ent = *it;

        // Colisiones con bloques (id == 2)
        if (ent->getId() == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {
            printf("colision con bloque\n");

            if (!ent) {
                ++it;
                continue;
            }

            if (collidingBottom(ent)) {
                speed.y = 0;
                hitbox.y = ent->getHitbox().y - hitbox.height;
                isJumping = false;
                onGround = true;
            }

            if (collidingAbove(ent)) {
                hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
                speed.y = 1.0f;

                if (SurpriseBlock* surprise = dynamic_cast<SurpriseBlock*>(ent)) {

                    surprise->decreaseState();
                }
            }

            if (CheckCollisionPointRec(left, ent->getHitbox())) {
                printf("collision left");
                hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
            }

            if (CheckCollisionPointRec(right, ent->getHitbox())) {
                printf("collision right");
                hitbox.x = ent->getHitbox().x - hitbox.width;
            }

            colliding = true;

            ++it;
            continue;
        }
        else {

            colliding = false;
            onGround = false;
        }

        // Colisiones con Goomba (id == 1)
        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->getId() == 1) {
            if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->getState() == 1) {

                if (!ent) {
                    ++it;
                    continue;
                }

                printf("COLLISION GOOMBA CON LOS PIES\n");

                PlaySound(jumpGoombaS);

                ent->decreaseState();

                jump(8.0f);

                delete ent;          // liberar memoria
                it = e.erase(it);    // borrar del vector y continuar
                continue;
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
        else {

            colliding = false;
        }

        ++it;
    }
}
