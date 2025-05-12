#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include <vector>

class Player : public Entity {

private:

#pragma region TEXTURES

#pragma region LITTLE MARIO


    Texture2D walkRight[4];
    Texture2D walkLeft[4];

    Texture2D jumplMarioL;
    Texture2D jumplMarioR;

    Texture2D deadMario;
#pragma endregion

#pragma region BIG MARIO

    Texture2D walkRightBig[4];
    Texture2D walkLeftBig[4];

    Texture2D jumpbMarioL;
    Texture2D jumpbMarioR;
#pragma endregion

#pragma region STAR MARIO

    Texture2D walkRightStar[4];
    Texture2D walkLeftStar[4];

    Texture2D jumpStarLeft;
    Texture2D jumpStarRight;
#pragma endregion
#pragma endregion

#pragma region SOUNDS
    Sound jumpSmallS;
    Sound jumpBigS;
    Sound marioDieS;
    Sound invisibilityS;
    Sound lostLife;
    Sound jumpGoombaS;
#pragma endregion

    int direction; //1 right / 0 left
    float time; //3.0f

    Vector2 speed;
    float movementSpeed;
    bool isJumping;
    bool colliding;
    bool immunity;
    bool isWalking;

    int hasPowerUp; // 0 is for nothing, 1 -> flower, 2 -> star

    //For spritesheet animation (NOT USED FOR NOW)
    Rectangle frameRec;
    int frameCounter;
    int currentFrame;
    float frameSpeed;
    float timer;

public:


    Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_, int hasPowerUp_);
    ~Player();

    void applyGravity(float gravity);
    void draw() override;
    bool shouldDrawMario(bool immunity);
    bool shouldUseStarSprite();
    void jump(float jumpForce);
    float getTime();
    void move(int direction, float cameraX);
    void immunityVoid();
    void colisionsPlayer(std::vector<Entity*>& e);
    void changeDirection();
    void isWalkingTrue();
    void isWalkingFalse();
    void modifyHitbox();
    void increaseState();
    void starPowerUpTimer();

   
#pragma region GETTERS
    //getterS
    int getDir() { return direction; }
    bool retImmunity() { return immunity; }
    bool retJumping() { return isJumping; }
    bool retColliding() { return colliding; }
    bool retIsWalking() { return isWalking; };
#pragma endregion
};
