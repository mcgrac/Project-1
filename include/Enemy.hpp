
#pragma once

#include "Entity.hpp"

class Enemy : public Entity {
protected:

    bool isDead;

public:

    Enemy(float x, float y, float width, float height, int id, int state);
    ~Enemy();
};

