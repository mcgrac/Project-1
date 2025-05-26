#pragma once
#include "raylib.h"
#include "Entity.hpp"
#include "SurpriseBlock.hpp"
#include"BreakBlock.hpp"
#include"BaseObject.hpp"
#include <vector>
#include "GameCamera.hpp"
#include "Fireball.hpp"
#include "Goomba.hpp"
#include"Piranha.hpp"
#include "Flag.hpp"

class Player : public Entity {

private:

#pragma region TEXTURES

#pragma region LITTLE MARIO


    Texture2D walkRight[4];
    Texture2D walkLeft[4];

    Texture2D jumplMarioL;
    Texture2D jumplMarioR;

    Texture2D deadMario;
#pragma endregion

#pragma region BIG MARIO

    Texture2D walkRightBig[4];
    Texture2D walkLeftBig[4];

    Texture2D jumpbMarioL;
    Texture2D jumpbMarioR;
#pragma endregion

#pragma region STAR MARIO

    Texture2D walkRightStar[4];
    Texture2D walkLeftStar[4];

    Texture2D jumpStarLeft;
    Texture2D jumpStarRight;
#pragma endregion

#pragma region FIRE MARIO
    Texture2D walkRightFire[4];
    Texture2D walkLeftFire[4];

    Texture2D jumpFireLeft;
    Texture2D jumpFireRight;
#pragma endregion

#pragma region FLAG ANIMATION

    //star
    Texture2D starMarioFlag[2];

    //fire
    Texture2D fireMarioFlag[2];

    //big
    Texture2D bMarioFlag[2];

    //small
    Texture2D sMarioFlag[2];

#pragma endregion

#pragma endregion

#pragma region SOUNDS
    Sound jumpSmallS;
    Sound marioDieS;
    Sound lostLife;
    Sound jumpGoombaS;
    Sound hitBlock;
    Sound getPowerUp;
    Sound getCoin;
#pragma endregion

    GameCamera* camera; // pointer to camera
    Flag* flag = nullptr; //pointer to flag for the final animation
    Vector2 scorePopupPos;

    int direction; //1 right / -1 left
    float time; 

    Vector2 speed;
    float movementSpeed;
    bool isJumping;
    bool colliding;
    bool immunity;
    bool isWalking;

    int hasPowerUp; // 0 is for nothing, 1 -> flower, 2 -> star
    int score;
    bool alive;
    bool flagAnimation;


    int frameCounter;
    int currentFrame;
    float frameSpeed;
    float timer; //this is used for the walking animations

public:


    Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_, int hasPowerUp_, GameCamera* cam_);
    ~Player();

    void applyGravity(float gravity, float delta);
    void draw() override;
    bool shouldDrawMario(bool immunity);
    bool shouldUseStarSprite();
    void jump(float jumpForce);
    float getTime();
    void move(int direction, float cameraX, float delta);
    void immunityVoid(float delta);
    void colisionsPlayer(std::vector<Entity*>& e);
    void changeDirection();
    void isWalkingTrue();
    void isWalkingFalse();
    void modifyHitbox();
    void increaseState();
    void starPowerUpTimer();
    void update(vector<Entity*>& entity, float gravity) override;
    void castFireball(vector<Entity*>& entity);

    void addScore(int scoreToAdd);

    void die(float gravity, float delta);

    void win(float delta);
   
#pragma region GETTERS
    //getterS
    int getDir() { return direction; }
    bool retImmunity() { return immunity; }
    bool retJumping() { return isJumping; }
    bool retColliding() { return colliding; }
    bool retIsWalking() { return isWalking; };
    int getScorePlayer() { return score; }
    bool getAlive() { return alive; }
    bool getFlagAnimation() { return flagAnimation; }
    bool getState() { return state; }
    int getHasPowerUp() { return hasPowerUp; }
#pragma endregion
};
