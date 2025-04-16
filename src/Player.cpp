#include "Player.hpp"
#include <cstdio>
#include<vector>

using namespace std;

Player::Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_)
    : Entity(x, y, width, height, id, state),
    speed{ speedX, speedY },
    movementSpeed(movementSpeed_),
    isJumping(false),
    onGround(false),
    colliding(false),
    immunity(false),
    time(3.0f),
    frameCounter(0),
    currentFrame(0),
    timer(0),
    frameSpeed(8),
    direction(direction_){

    //textures
    littleMarioR = LoadTexture("resources/mario1.png");
    littleMarioL = LoadTexture("resources/Lmario1.png");

    bMarioWalkLeft = LoadTexture("resources/walking_animation0.png");
    bMarioWalkRight = LoadTexture("resources/walking_animation1.png");

    jumpMarioL = LoadTexture("resources/bMarioJumpL.png");
    jumpMarioR = LoadTexture("resources/bMarioJumpR.png");

    //sounds
    jumpSound = LoadSound("resources/audio/jumpSmall.wav");
    //SetSoundVolume(jumpSound, 1.0f); // Set proper volume
    jumpGoombaS = LoadSound("resources/audio/smb_stomp.wav");
}

Player::~Player() {

    UnloadTexture(littleMarioR);
    UnloadTexture(littleMarioL);

    UnloadSound(jumpSound);
    UnloadSound(jumpGoombaS);
}

void Player::draw() {

    //frameCounter++;

    /*Rectangle rec = frameRec;

    int frameWidth = littleMarioL.width / 4;
    int frameHeigh = littleMarioL.height;

    rec = { 0,0,(float)frameWidth, (float)frameHeigh };

    float delta = GetFrameTime();
    timer += delta;*/

    //if (timer >= frameSpeed) {
    //    timer = 0.0f;
    //    currentFrame++;
    //    if (currentFrame > 3) currentFrame = 0; // volvemos al primer frame
    //    frameRec.x = (float)currentFrame * frameWidth;
    //}



    //if (onGround) {
    //    if (frameCounter >= (60 / frameSpeed)) {
    //        frameCounter = 0;
    //        currentFrame++;
    //        if (currentFrame > 3) currentFrame = 0;
    //    }

    //    frameRec.x = (float)currentFrame * frameRec.width;
    //}

    //Texture2D currentTexture;

    //if (direction == 0) {
    //    // Dirección derecha
    //    if (onGround) {
    //        // Mario grande caminando en el suelo, derecha
    //        currentTexture = bMarioWalkRight;
    //        DrawTextureRec(currentTexture, frameRec, { hitbox.x, hitbox.y-16 }, WHITE);
    //    }
    //    else {
    //        // Mario grande saltando, derecha
    //        currentTexture = jumpMarioR;
    //        DrawTexture(currentTexture, hitbox.x, hitbox.y-16, WHITE);
    //    }
    //}
    //else {
    //    // Dirección izquierda
    //    if (onGround) {
    //        // Mario grande caminando en el suelo, izquierda
    //        currentTexture = bMarioWalkLeft;
    //        DrawTextureRec(currentTexture, frameRec, { hitbox.x, hitbox.y-16 }, WHITE);
    //    }
    //    else {
    //        // Mario grande saltando, izquierda
    //        currentTexture = jumpMarioL;
    //        DrawTexture(currentTexture, hitbox.x, hitbox.y-16, WHITE);
    //    }
    //}


    if (direction == 1) {

        if (immunity) {

             //to show is immune mario will blink
            if (((int)(GetTime() * 10) % 2) == 0) {

                printf("----------------------parpadeando------------------");
                DrawTexture(littleMarioR, hitbox.x, hitbox.y, WHITE);
                //DrawTextureRec(bMarioWalkRight, frameRec, Vector2{ hitbox.x, hitbox.y }, WHITE);
            }
        }
        else {

            DrawTexture(littleMarioR, hitbox.x, hitbox.y, WHITE);
            //DrawTextureRec(bMarioWalkRight, frameRec, Vector2{ hitbox.x, hitbox.y }, WHITE);
        }

    }
    else {

        if (immunity) {

            //to show is immune mario will "parpadear"
            if (((int)(GetTime() * 10) % 2) == 0) {

                printf("----------------------parpadeando------------------");
                DrawTexture(littleMarioL, hitbox.x, hitbox.y, WHITE);
                //DrawTextureRec(littleMarioL, frameRec, Vector2{ hitbox.x, hitbox.y }, WHITE);
            }
        }
        else {

            DrawTexture(littleMarioL, hitbox.x, hitbox.y, WHITE);
            //DrawTextureRec(littleMarioL, frameRec, Vector2{ hitbox.x, hitbox.y }, WHITE);
        }
    }


}

void Player::jump(float jumpForce) {
    if (!isJumping || !colliding) {
        speed.y = -jumpForce;
        isJumping = true;
    }

    //InitAudioDevice();
    if (!IsSoundPlaying(jumpSound) && !IsSoundPlaying(jumpGoombaS)) {

        PlaySound(jumpSound);
    }

}

float Player::getTime() {
    return time;
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

    //printf("Mario position: x->%f / y->%f\n", hitbox.x, hitbox.y);

    //Aplicar gravedad a MArio
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

    float leftLimit = cameraX - 512.0f / 2.0f; // borde izquierdo visible

    if (nextX >= leftLimit) {
        hitbox.x = nextX;
    }
    else {
        hitbox.x = leftLimit; // lo deja justo al borde visible
    }
}

void Player::immunityVoid() {
    if (immunity) {
        time -= GetFrameTime();
        if (time <= 0) {
            immunity = false;
            time = 3;
        }
    }
}

//void Player::colisionsPlayer(vector<Entity*>& e) {
//
//    for (auto it = e.begin(); it != e.end(); ) {
//        Entity* ent = *it;
//
//        // Colisiones con bloques (id == 2)
//        if (ent->id == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {
//            printf("colision con bloque\n");
//
//            if (collidingBottom(ent)) {
//                speed.y = 0;
//                hitbox.y = ent->getHitbox().y - hitbox.height;
//                isJumping = false;
//                onGround = true;
//            }
//
//            if (collidingAbove(ent)) {
//                hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
//                speed.y = 1.0f;
//            }
//
//            if (CheckCollisionPointRec(left, ent->getHitbox())) {
//                hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
//            }
//
//            if (CheckCollisionPointRec(right, ent->getHitbox())) {
//                hitbox.x = ent->getHitbox().x - hitbox.width;
//            }
//
//            colliding = true;
//
//            ++it;
//            continue;
//        }
//        else {
//
//            colliding = false;
//            onGround = false;
//        }
//
//        // Colisiones con Goomba (id == 1)
//        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->id == 1) {
//            if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->state == 1) {
//                printf("COLLISION GOOMBA CON LOS PIES\n");
//
//                PlaySound(jumpGoombaS);
//
//                ent->state = 0;
//
//                jump(8.0f);
//
//                delete ent;          // liberar memoria
//                it = e.erase(it);    // borrar del vector y continuar
//                continue;
//            }
//            else {
//                printf("COLISION CON GOOMBA\n");
//
//                state--;
//                if (state == 0) {
//                    // Mario muere
//                }
//                else {
//                    immunity = true;
//                }
//            }
//        }
//        else {
//
//            colliding = false;
//        }
//
//        ++it;
//    }
//}
