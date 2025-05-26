
#pragma once

#include "Entity.hpp"

class Enemy : public Entity {
private:

    char typeEnemy; //'g'-> goomba, 'p'->piranha

public:

    Enemy(float x, float y, float width, float height, int id, int state, char typeEnemy_);
    ~Enemy();

    //getter
    char getTypeEnemy() { return typeEnemy; }
};

