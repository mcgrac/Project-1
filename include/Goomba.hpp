#pragma once

#include "Enemy.hpp"
#include <vector>

class Goomba : public Enemy {

private:
    Texture2D goomba1;
    Texture2D goomba2;
    Texture2D goombaDeadT;

    //sounds
    Sound goombaDieS;

    //Rectangle frameRec;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameSpeed = 10;

protected:
    float movementSpeed;
    int direction;

public:
    Goomba(float x, float y, float width, float height, int id, int state, float movementSpeed_, int direction_);
    ~Goomba();

    float getMovementSpeed();

    void draw() override;

    void moveGoomba(std::vector<Entity*> entity);

    void colisionsGoomba(std::vector<Entity> e);

    void die(Entity*& e, vector<Entity*>& list, int index);
};
