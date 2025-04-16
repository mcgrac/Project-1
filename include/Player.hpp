#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include <vector>

class Player : public Entity {

private:

    Texture2D littleMarioR;
    Texture2D littleMarioL;

    Texture2D bMarioWalkRight;
    Texture2D bMarioWalkLeft;

    Texture2D jumpMarioL;
    Texture2D jumpMarioR;

    Sound jumpSound, jumpGoombaS;

    int direction; //1 right / 0 left
    float time;

    Vector2 speed;
    float movementSpeed;
    bool isJumping;
    bool onGround;
    bool colliding;
    bool immunity;

    Rectangle frameRec;
    int frameCounter;
    int currentFrame;
    int frameSpeed;
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

    //getter
    int getDir() { return direction; }
    bool retImmunity() { return immunity; }
    bool retJumping() { return isJumping; }
    bool retColliding() { return colliding; }
};
