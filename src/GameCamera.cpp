#include "GameCamera.hpp"

GameCamera::GameCamera(float screenWidth, float mapStartX, float mapEndX, float followThreshold)
    : screenWidth(screenWidth), mapStartX(mapStartX), mapEndX(mapEndX), followThreshold(followThreshold)
{
    camera.offset = { screenWidth / 2.0f, 0 };
    camera.target = { 256, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void GameCamera::update(Rectangle playerPosition) {
    // Posición de umbral absoluto (en mundo) desde donde empieza a seguir al jugador
    float maxPlayerX = camera.target.x + screenWidth * (followThreshold - 0.5f);

    // Si el jugador lo supera, mover la cámara hacia adelante
    if (playerPosition.x > maxPlayerX) {
        float delta = playerPosition.x - maxPlayerX;
        camera.target.x += delta;
    }

    // No permitir que retroceda
    float minCameraX = mapStartX + screenWidth / 2.0f;
    if (camera.target.x < minCameraX)
        camera.target.x = minCameraX;

    // No permitir que pase el final del mapa
    float maxCameraX = mapEndX - screenWidth / 2.0f;
    if (camera.target.x > maxCameraX)
        camera.target.x = maxCameraX;

    camera.target.y = 0;
}

void GameCamera::reset() {

    printf("target en x antes: %f", camera.target.x);

    camera.target.x = 256;
    camera.target.y = 0;

    printf("target en x despues: %f", camera.target.x);
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
