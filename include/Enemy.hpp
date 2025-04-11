
#pragma once

#include "Entity.hpp"

class Enemy : public Entity {
public:
    Enemy(float x, float y, float width, float height, int id, int state);
};

