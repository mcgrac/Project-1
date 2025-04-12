#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include <vector>

class Player : public Entity {

private:

    Texture2D big_mario0;
    Texture2D big_mario1;
    Texture2D big_mario_jump0;
    Texture2D big_mario_jump1;

    Rectangle frameRec;
    int frameCounter;
    int currentFrame;
    int frameSpeed;
    int direction; //1 right / 0 left
    float time;

public:
    Vector2 speed;
    float movementSpeed;
    bool isJumping;
    bool onGround;
    bool colliding;
    bool immunity;

    Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_);

    void applyGravity(float gravity);
    void draw() override;
    void jump(float jumpForce);
    float getTime();
    void move(int direction);
    void immunityVoid(Player& mario);
    //void colisionsPlayerEnemy(std::vector<Entity> enemy);
    void colisionsPlayer(std::vector<Entity*> e);
    void changeDirection();

    //getter
    int getDir() { return direction; }
};
