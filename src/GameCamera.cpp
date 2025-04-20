#include "GameCamera.hpp"

GameCamera::GameCamera(float screenWidth, float mapStartX, float mapEndX, float followThreshold)
    : screenWidth(screenWidth), mapStartX(mapStartX), mapEndX(mapEndX), followThreshold(followThreshold)
{
    //set the values of the proprties of the camera
    camera.offset = { screenWidth / 2.0f, 0 }; //where is placed the camera in relation of the screen
    camera.target = { 256, 0 }; //what will follow the camera
    camera.rotation = 0.0f; //rotation
    camera.zoom = 1.0f; //zoom
}

void GameCamera::update(Rectangle playerPosition) {
    // Global position that te camera will start following the character
    float maxPlayerX = camera.target.x + screenWidth * (followThreshold - 0.5f);

    // If player position is more than that, camera will start following
    if (playerPosition.x > maxPlayerX) {
        float delta = playerPosition.x - maxPlayerX;
        camera.target.x += delta;
    }

    //avoid the camera to go back
    float minCameraX = mapStartX + screenWidth / 2.0f;
    if (camera.target.x < minCameraX)
        camera.target.x = minCameraX;

    //avoid camera going out the map
    float maxCameraX = mapEndX - screenWidth / 2.0f;
    if (camera.target.x > maxCameraX)
        camera.target.x = maxCameraX;

    //the camera will only move on x-axis
    camera.target.y = 0;
}

void GameCamera::reset() {

    //reseting values
    camera.target.x = 256;
    camera.target.y = 0;
}

void GameCamera::begin() {
    BeginMode2D(camera);
}

void GameCamera::end() {
    EndMode2D();
}

Camera2D GameCamera::getRawCamera() const {
    return camera;
}