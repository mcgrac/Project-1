#include "Player.hpp"
#include <cstdio>
#include<vector>
#include "SurpriseBlock.hpp"

using namespace std;

Player::Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_)
    : Entity(x, y, width, height, id, state),
    speed{ speedX, speedY },
    movementSpeed(movementSpeed_),
    isJumping(false),
    colliding(false),
    immunity(false),
    isWalking(false),
    time(3.0f),
    frameCounter(0),
    currentFrame(0),
    timer(0),
    frameSpeed(0.1f),
    direction(direction_){

#pragma region TEXTURES
#pragma region LITTLE MARIO

    walkRight[0] = LoadTexture("resources/textures/mario1.png");
    walkRight[1] = LoadTexture("resources/textures/mario2.png");
    walkRight[2] = LoadTexture("resources/textures/mario3.png");
    walkRight[3] = LoadTexture("resources/textures/mario4.png");

    walkLeft[0] = LoadTexture("resources/textures/Lmario1.png");
    walkLeft[1] = LoadTexture("resources/textures/Lmario2.png");
    walkLeft[2] = LoadTexture("resources/textures/Lmario3.png");
    walkLeft[3] = LoadTexture("resources/textures/Lmario4.png");


    jumplMarioL = LoadTexture("resources/textures/Lmario5.png");
    jumplMarioR = LoadTexture("resources/textures/mario5.png");
#pragma endregion

#pragma region BIG MARIO

    walkRightBig[0] = LoadTexture("resources/textures/bmario1.png");
    walkRightBig[1] = LoadTexture("resources/textures/bmario2.png");
    walkRightBig[2] = LoadTexture("resources/textures/bmario3.png");
    walkRightBig[3] = LoadTexture("resources/textures/bmario4.png");

    walkLeftBig[0] = LoadTexture("resources/textures/Lbmario1.png");
    walkLeftBig[1] = LoadTexture("resources/textures/Lbmario2.png");
    walkLeftBig[2] = LoadTexture("resources/textures/Lbmario3.png");
    walkLeftBig[3] = LoadTexture("resources/textures/Lbmario4.png");

    jumpbMarioL = LoadTexture("resources/textures/bMarioJumpL.png");
    jumpbMarioR = LoadTexture("resources/textures/bMarioJumpR.png");
#pragma endregion
#pragma endregion

#pragma region SOUNDS
    //sounds
    jumpSmallS = LoadSound("resources/audio/JumpSmall.wav");
    SetSoundVolume(jumpSmallS, 0.4f);
    jumpBigS = LoadSound("resources/audio/JumpBig.wav");
    SetSoundVolume(jumpBigS, 0.4f);
    marioDieS = LoadSound("resources/audio/MarioDie.wav");
    invisibilityS = LoadSound("resources/audio/InvisibilityTheme.wav");
    lostLife = LoadSound("resources/audio/LostLife.wav");
    jumpGoombaS = LoadSound("resources/audio/smb_stomp.wav");
#pragma endregion
    updateRects();
}

Player::~Player() { //destructor -> unload everithing from memory

#pragma region TEXTURES

#pragma region SMALL MARIO
    UnloadTexture(walkRight[0]);
    UnloadTexture(walkRight[1]);
    UnloadTexture(walkRight[2]);
    UnloadTexture(walkRight[3]);

    UnloadTexture(walkLeft[0]);
    UnloadTexture(walkLeft[1]);
    UnloadTexture(walkLeft[2]);
    UnloadTexture(walkLeft[3]);

    UnloadTexture(jumplMarioL);
    UnloadTexture(jumplMarioR);
#pragma endregion
#pragma region BIG MARIO
    UnloadTexture(walkRightBig[0]);
    UnloadTexture(walkRightBig[1]);
    UnloadTexture(walkRightBig[2]);
    UnloadTexture(walkRightBig[3]);

    UnloadTexture(walkLeftBig[0]);
    UnloadTexture(walkLeftBig[1]);
    UnloadTexture(walkLeftBig[2]);
    UnloadTexture(walkLeftBig[3]);

    UnloadTexture(jumpbMarioL);
    UnloadTexture(jumpbMarioR);
#pragma endregion

#pragma endregion

#pragma region SOUNDS
    UnloadSound(jumpSmallS);
    UnloadSound(jumpBigS);
    UnloadSound(marioDieS);
    UnloadSound(invisibilityS);
#pragma endregion


}

void Player::modifyHitbox() { //this is used for mofifyng the hitbox when mario goes from big to little

    switch (state) {

    case 1: //little mario

        hitbox.width = walkLeft[0].width;
        hitbox.height = walkLeft[0].height;
        break;

    case 2: //big mario

        hitbox.width = walkLeftBig[0].width;
        hitbox.height = walkLeftBig[0].height;
        break;

    default:
        break;
    }
}
void Player::isWalkingTrue() { //called while the key arrows are pressed
    isWalking = true;
}
void Player::isWalkingFalse() { //called when the move keys are unpressed
    isWalking = false;
}

bool Player::shouldDrawMario(bool immunity) {
    if (!immunity) return true; //if immunity is false it will return true -> it should draw mario
    return ((int)(GetTime() * 10) % 2) == 0;//return true and false continiouslt for making the blinking effect
}

float Player::getTime() { //get the time in game
    return time;
}

void Player::draw() {

    
    if (isWalking) { //only run timer if mario is walking
        timer += GetFrameTime();
    }


    if (timer >= frameSpeed) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4; // between 0 and 3
    }

    Vector2 position = { hitbox.x, hitbox.y }; //get the position of mario

    switch (state) {
    case 1: // small mario
        if (!isJumping) { //not jumping
            if (direction == 1) { // right
                if (isWalking) {//if is walking show animation
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkRight[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkRight[0], position.x, position.y, WHITE);
                    }
                }
            }
            else { // left
                if (isWalking) {//if is walking show animation
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkLeft[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkLeft[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else { // jumping
            if (direction == 1) {// right
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioR, position.x, position.y, WHITE);
                }
            }
            else {// left
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioL, position.x, position.y, WHITE);
                }
            }
        }
        break;

    case 2: // Big mario
        if (!isJumping) {//not jumping
            if (direction == 1) { // right
                if (isWalking) { //if is walking show animation
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkRightBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else { //if not show idle sprite
                    if (shouldDrawMario(immunity)) { //Do the blinking effect
                        DrawTexture(walkRightBig[0], position.x, position.y, WHITE);
                    }
                }
            }
            else { // left
                if (isWalking) {//if is walking show animation
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkLeftBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {//Do the blinking effect
                        DrawTexture(walkLeftBig[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else { // jumping
            if (direction == 1) {// right
                if (shouldDrawMario(immunity)) {//Do the blinking effect
                    DrawTexture(jumpbMarioR, position.x, position.y, WHITE);
                }
            }
            else {// left
                if (shouldDrawMario(immunity)) {//Do the blinking effect
                    DrawTexture(jumpbMarioL, position.x, position.y, WHITE);
                }
            }
        }
        break;

    default:
        break;
    }
}

void Player::jump(float jumpForce) {
    if (!isJumping || !colliding) { //jump if it's not jumping or it has hitted a goomba(colliding will only be true when colliding blocks)
        speed.y = -jumpForce;
        isJumping = true; //avoids jumping continiously
    }

    if (!IsSoundPlaying(jumpSmallS) && !IsSoundPlaying(jumpGoombaS)) { // do the normal jump sound

        PlaySound(jumpSmallS);
    }

}

void Player::changeDirection() {

    if (direction == 1) { 
        
        direction = 0; 
    }
    else if (direction == 0) {

        direction = 1;
    }
}

void Player::applyGravity(float gravity) {

    //Apply gravity
    speed.y += gravity;
    hitbox.y += speed.y;
}
void Player::move(int direction, float cameraX) {
    float nextX = hitbox.x;

    if (direction == 1) {
        nextX += movementSpeed;
    }
    else {
        nextX -= movementSpeed;
    }

    float leftLimit = cameraX - 512.0f / 2.0f; // left side visible of the screen

    if (nextX >= leftLimit) {
        hitbox.x = nextX;
    }
    else {
        hitbox.x = leftLimit; // blocks mario from going ouside this limit
    }
}

void Player::immunityVoid() {
    if (immunity) {
        time -= GetFrameTime(); //counts back from 3 to 0
        if (time <= 0) { //counts until three, which is the time of immunity
            immunity = false;
            time = 3;
        }
    }
}

void Player::colisionsPlayer(vector<Entity*>& e) {

    //we use an itarator here because we don't want to make acces to deleted memory
    //we traverse the vector of entities until the end of the list, not having in account the size, because it might change when deleting something

    for (auto it = e.begin(); it != e.end(); ) { 
        Entity* ent = *it;

        // Collision with blocks (id == 2)
        if (ent->getId() == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {
            printf("colision con bloque\n");

            if (!ent) { //if the pointer is null
                ++it; //next iteration
                continue;
            }

            //for checking collisions we use the middle pints of each side and define a different behaviour for each one of them

            if (CheckCollisionPointRec(bottom, ent->getHitbox())) { //collision bottom (floor)
                speed.y = 0;
                hitbox.y = ent->getHitbox().y - hitbox.height;
                isJumping = false;
            }

            if (CheckCollisionPointRec(top, ent->getHitbox())) { //collision above (head)
                hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
                speed.y = 1.0f;

                if (SurpriseBlock* surprise = dynamic_cast<SurpriseBlock*>(ent)) { //do a dynamyc cast to know if that pointer has a surpirseBlock element to acces to it

                    surprise->decreaseState();
                }
            }

            if (CheckCollisionPointRec(left, ent->getHitbox())) { //collision left side
                printf("collision left");
                hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
            }

            if (CheckCollisionPointRec(right, ent->getHitbox())) { //collision right side
                printf("collision right");
                hitbox.x = ent->getHitbox().x - hitbox.width;
            }

            colliding = true;

            ++it; //next iteration
            continue; //use continuo for going outside and to the next iteration
        }
        else {

            colliding = false;
        }

        // Collisions with goomba (id == 1)
        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->getId() == 1) {
            if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->getState() == 1) { //collision with mario's feet

                if (!ent) {
                    ++it; //next iteration
                    continue; //use continuo for going outside and to the next iteration
                }

                printf("COLLISION GOOMBA CON LOS PIES\n");

                PlaySound(jumpGoombaS);

                ent->decreaseState();

                jump(8.0f);

                delete ent;          // feee memory
                it = e.erase(it);    // delete from the vector and continue
                continue; //use continuo for going outside and to the next iteration
            }
            else { //collision with the rest of the body
                printf("COLISION CON GOOMBA\n");

                state--;
                if (state == 0) {
                    // Mario die
                }
                else {
                    modifyHitbox(); //modify its hitbox when its hitted
                    immunity = true;
                }
            }
        }
        else {

            colliding = false;
        }

        ++it; //next iteration
    }
}
