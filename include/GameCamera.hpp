#pragma once
#include"raylib.h"
#include"iostream"

class GameCamera {
private:
    Camera2D camera;
    float mapStartX;
    float mapEndX;
    float screenWidth;
    float followThreshold; //this is used for setting that the camera will only start to follow mario if he is in the third section of the screen

public:
    GameCamera(float screenWidth, float mapStartX, float mapEndX, float followThreshold = 0.66f);

    void update(Rectangle playerPosition);
    void begin();
    void end();
    void reset();
    Camera2D getRawCamera() const;
};