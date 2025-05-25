#pragma once
#include "raylib.h"
#include "BaseObject.hpp"

class Mushroom : public BaseObject {
private:
    Texture2D mushroom;
    Vector2 velocity{ 0.0f, 0.0f };
    const float terminalVelocityY = 500.0f;
    const float initialSpeed = 60.0f;

    bool emerging = false;
    float emergedSoFar = 0.0f;
    const float maxEmerge = 16.0f;
    const float emergeSpeed = 1.0f;

public:
    Mushroom(float x, float y, float width, float height, int id, int state, int typePower_);
    ~Mushroom();

    void throwPower() override;
    void update(vector<Entity*>& entity, float gravity) override;
    void draw() override;

    void handleCollision();
};

