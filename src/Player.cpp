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

#pragma region TEXTURES
#pragma region LITTLE MARIO

    walkRight[0] = LoadTexture("resources/textures/mario1.png");
    walkRight[1] = LoadTexture("resources/textures/mario2.png");
    walkRight[2] = LoadTexture("resources/textures/mario3.png");
    walkRight[3] = LoadTexture("resources/textures/mario4.png");

    walkLeft[0] = LoadTexture("resources/textures/Lmario1.png");
    walkLeft[1] = LoadTexture("resources/textures/Lmario2.png");
    walkLeft[2] = LoadTexture("resources/textures/Lmario3.png");
    walkLeft[3] = LoadTexture("resources/textures/Lmario4.png");


    jumplMarioL = LoadTexture("resources/textures/Lmario5.png");
    jumplMarioR = LoadTexture("resources/textures/mario5.png");
#pragma endregion

#pragma region BIG MARIO

    walkRightBig[0] = LoadTexture("resources/textures/bmario1.png");
    walkRightBig[1] = LoadTexture("resources/textures/bmario2.png");
    walkRightBig[2] = LoadTexture("resources/textures/bmario3.png");
    walkRightBig[3] = LoadTexture("resources/textures/bmario4.png");

    //bMarioR1 = LoadTexture("resources/textures/bmario1.png");
    //bMarioR2 = LoadTexture("resources/textures/bmario2.png");
    //bMarioR3 = LoadTexture("resources/textures/bmario3.png");
    //bMarioR4 = LoadTexture("resources/textures/bmario4.png");

    walkLeftBig[0] = LoadTexture("resources/textures/Lbmario1.png");
    walkLeftBig[1] = LoadTexture("resources/textures/Lbmario2.png");
    walkLeftBig[2] = LoadTexture("resources/textures/Lbmario3.png");
    walkLeftBig[3] = LoadTexture("resources/textures/Lbmario4.png");

    //bMarioL1 = LoadTexture("resources/textures/Lbmario1.png");
    //bMarioL2 = LoadTexture("resources/textures/Lbmario2.png");
    //bMarioL3 = LoadTexture("resources/textures/Lbmario3.png");
    //bMarioL4 = LoadTexture("resources/textures/Lbmario4.png");

    jumpbMarioL = LoadTexture("resources/textures/bMarioJumpL.png");
    jumpbMarioR = LoadTexture("resources/textures/bMarioJumpR.png");
#pragma endregion
#pragma endregion


    //sounds
    jumpSound = LoadSound("resources/audio/jumpSmall.wav");
    jumpGoombaS = LoadSound("resources/audio/smb_stomp.wav");

    updateRects();
}

Player::~Player() {

    UnloadTexture(walkRight[0]);
    UnloadTexture(walkRight[1]);
    UnloadTexture(walkRight[2]);
    UnloadTexture(walkRight[3]);

    UnloadTexture(walkLeft[0]);
    UnloadTexture(walkLeft[1]);
    UnloadTexture(walkLeft[2]);
    UnloadTexture(walkLeft[3]);

    UnloadTexture(jumplMarioL);
    UnloadTexture(jumplMarioR);

    UnloadTexture(walkRightBig[0]);
    UnloadTexture(walkRightBig[1]);
    UnloadTexture(walkRightBig[2]);
    UnloadTexture(walkRightBig[3]);

    UnloadTexture(walkLeftBig[0]);
    UnloadTexture(walkLeftBig[1]);
    UnloadTexture(walkLeftBig[2]);
    UnloadTexture(walkLeftBig[3]);

    UnloadTexture(jumpbMarioL);
    UnloadTexture(jumpbMarioR);

    UnloadSound(jumpSound);
    UnloadSound(jumpGoombaS);
}

void Player::modifyHitbox() {

    switch (state) {

    case 1: //little mario

        hitbox.width = walkLeft[0].width;
        hitbox.height = walkLeft[0].height;
        break;

    case 2: //big mario

        hitbox.width = walkLeftBig[0].width;
        hitbox.height = walkLeftBig[0].height;
        break;

    default:
        break;
    }
}
void Player::isWalkingTrue() {
    isWalking = true;
}
void Player::isWalkingFalse() {
    isWalking = false;
}

bool Player::shouldDrawMario(bool immunity) {
    if (!immunity) return true;
    return ((int)(GetTime() * 10) % 2) == 0;
}

void Player::draw() {

    
    if (isWalking) { //only run timer if mario is walking
        timer += GetFrameTime();
    }


    if (timer >= frameSpeed) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4; // between 0 and 3
    }

    Vector2 position = { hitbox.x, hitbox.y };

    switch (state) {
    case 1: // Big mario
        if (!isJumping) {
            if (direction == 1) { // right
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRight[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRight[0], position.x, position.y, WHITE);
                    }
                }
            }
            else { // left
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeft[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeft[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else { // jumping
            if (direction == 1) {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioR, position.x, position.y, WHITE);
                }
            }
            else {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioL, position.x, position.y, WHITE);
                }
            }
        }
        break;

    case 2: // Big mario
        if (!isJumping) {
            if (direction == 1) { // right
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRightBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRightBig[0], position.x, position.y, WHITE);
                    }
                }
            }
            else { // left
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeftBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeftBig[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else { // jumping
            if (direction == 1) {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumpbMarioR, position.x, position.y, WHITE);
                }
            }
            else {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumpbMarioL, position.x, position.y, WHITE);
                }
            }
        }
        break;

    default:
        break;
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
                    modifyHitbox(); //modify its hitbox
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
