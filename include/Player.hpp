#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include <vector>

class Player : public Entity {

private:

#pragma region TEXTURES

#pragma region LITTLE MARIO


    Texture2D walkRight[4];
    Texture2D lMarioR1;
    Texture2D lMarioR2;
    Texture2D lMarioR3;
    Texture2D lMarioR4;

    Texture2D walkLeft[4];
    Texture2D lMarioL1;
    Texture2D lMarioL2;
    Texture2D lMarioL3;
    Texture2D lMarioL4;

    Texture2D jumplMarioL;
    Texture2D jumplMarioR;
#pragma endregion

#pragma region BIG MARIO
    Texture2D bMarioR1;
    Texture2D bMarioR2;
    Texture2D bMarioR3;
    Texture2D bMarioR4;

    Texture2D bMarioL1;
    Texture2D bMarioL2;
    Texture2D bMarioL3;
    Texture2D bMarioL4;

    Texture2D jumpbMarioL;
    Texture2D jumpbMarioR;
#pragma endregion


    //Texture2D littleMarioR;
    //Texture2D littleMarioL;
    //Texture2D bMarioWalkRight;
    //Texture2D bMarioWalkLeft;
    //Texture2D jumpMarioL;
    //Texture2D jumpMarioR;
#pragma endregion

#pragma region SOUNDS
    Sound jumpSound, jumpGoombaS;
#pragma endregion

    int direction; //1 right / 0 left
    float time;

    Vector2 speed;
    float movementSpeed;
    bool isJumping;
    bool onGround;
    bool colliding;
    bool immunity;
    bool isWalking;

    //For spritesheet animation
    Rectangle frameRec;
    int frameCounter;
    int currentFrame;
    float frameSpeed;
    float timer;

public:


    Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_);
    ~Player();

    void applyGravity(float gravity);
    void draw() override;
    void jump(float jumpForce);
    float getTime();
    void move(int direction, float cameraX);
    void immunityVoid();
    void colisionsPlayer(std::vector<Entity*>& e);
    void changeDirection();
    void isWalkingTrue();
    void isWalkingFalse();

    //getter
    int getDir() { return direction; }
    bool retImmunity() { return immunity; }
    bool retJumping() { return isJumping; }
    bool retColliding() { return colliding; }
    bool retIsWalking() { return isWalking; };
};
