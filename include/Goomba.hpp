#pragma once

#include "Enemy.hpp"
#include <vector>

class Goomba : public Enemy {

private:

#pragma region TEXTURES
    Texture2D goomba1;
    Texture2D goomba2;
    Texture2D goombaDeadT;
#pragma endregion

#pragma region SOUNDS
    //sounds
    Sound goombaDieS;
#pragma endregion

    //Rectangle frameRec (ANIMATION)
    int frameCounter = 0;
    int currentFrame = 0;
    int frameSpeed = 10;

    bool touched = false;
    float clock = 0.0f;

protected:
    float movementSpeed;
    int direction;

public:
    Goomba(float x, float y, float width, float height, int id, int state, float movementSpeed_, int direction_);
    ~Goomba();

    float getMovementSpeed();

    void draw() override;

    void update();

    void die();
    void moveGoomba(vector<Entity*>& entity, float gravity);
    void collisionGoomba(vector<Entity*>& entity);
};
