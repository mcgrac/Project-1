#pragma once

#include "raylib.h"
#include "Entity.hpp"

// BaseObject: common functionality for all power-ups
class BaseObject : public Entity {
protected:
    int typePower;         // 0->mushroom, 1->flower, 2->star

    bool emerging = true;  // initially popping out of the block
    float emergeSpeed = 0.7f;
    float emergedSoFar = 0.0f;
    const float maxEmerge = 16.0f;
    Vector2 velocity{ 0,0 }; // default zero

public:
    BaseObject(float x, float y, float width, float height,
        int id, int state, int typePower_);
    virtual ~BaseObject() = default;

    // Pop the power-up out of its block
    virtual void throwPower() {}

    // Update per-frame (handle emerging or physics)
    virtual void update(float gravity) = 0;

    // Draw the power-up
    virtual void draw() = 0;

    int getTypePowerUp() const { return typePower; }
};
