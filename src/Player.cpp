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
    direction(direction_){

    littleMarioR = LoadTexture("resources/mario1.png");
    littleMarioL = LoadTexture("resources/Lmario1.png");

}

void Player::draw() {

    if (direction == 1) {

        if (immunity) {
             //to show is immune mario will "parpadear"
            if (((int)(GetTime() * 10) % 2) == 0) {

                printf("----------------------parpadeando------------------");
                DrawTexture(littleMarioR, hitbox.x, hitbox.y, WHITE);
            }
        }
        else {

            DrawTexture(littleMarioR, hitbox.x, hitbox.y, WHITE);
        }

    }
    else {

        if (immunity) {

            //to show is immune mario will "parpadear"
            if (((int)(GetTime() * 10) % 2) == 0) {

                printf("----------------------parpadeando------------------");
                DrawTexture(littleMarioL, hitbox.x, hitbox.y, WHITE);
            }
        }
        else {

            DrawTexture(littleMarioL, hitbox.x, hitbox.y, WHITE);
        }
    }


}

void Player::jump(float jumpForce) {
    if (!isJumping) {
        speed.y = -jumpForce;
        isJumping = true;
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

    printf("Mario position: x->%f / y->%f\n", hitbox.x, hitbox.y);

    //Aplicar gravedad a MArio
    speed.y += gravity;
    hitbox.y += speed.y;
}
void Player::move(int direction) {


    if (direction == 1) {
        hitbox.x += movementSpeed;
    }
    else {
        hitbox.x -= movementSpeed;
    }
}

void Player::immunityVoid(Player& mario) {
    if (mario.immunity) {
        mario.time -= GetFrameTime();
        if (mario.time <= 0) {
            mario.immunity = false;
            mario.time = 3;
        }
    }
}

//void Player::colisionsPlayerEnemy(std::vector<Entity> enemy) {
//    for (int i = 0; i < enemy.size(); ++i) {
//        if (CheckCollisionRecs(hitbox, enemy[i].hitbox) && enemy[i].id == 1 && !immunity) {
//            printf("COLISION CON GOOMBA\n");
//
//            if (CheckCollisionPointRec(bottom, enemy[i].hitbox)) {
//                enemy[i].state = 0;
//                jump(8.0f);
//            }
//            else {
//                state--;
//                if (state == 0) {
//                    // Mario muere
//                }
//                else {
//                    immunity = true;
//                }
//            }
//        }
//    }
//}

void Player::colisionsPlayer(vector<Entity*> e) {
    for (int i = 0; i < e.size(); ++i) {
        if (e[i]->id == 2 && CheckCollisionRecs(hitbox, e[i]->getHitbox())) {
            printf("colision con bloque\n");

            if (collidingBottom(e[i])) {
                speed.y = 0;
                hitbox.y = e[i]->getHitbox().y - hitbox.height;
                isJumping = false;
            }

            if (collidingAbove(e[i])) {
                hitbox.y = e[i]->getHitbox().y + e[i]->getHitbox().height;
                speed.y = 1.0f;
            }

            if (CheckCollisionPointRec(left, e[i]->getHitbox())) {
                hitbox.x = e[i]->getHitbox().x + e[i]->getHitbox().width;
            }

            if (CheckCollisionPointRec(right, e[i]->getHitbox())) {
                hitbox.x = e[i]->getHitbox().x - e[i]->getHitbox().width;
            }
        }

        if (CheckCollisionRecs(hitbox, e[i]->getHitbox()) && !immunity && e[i]->id == 1) {


            if (CheckCollisionPointRec(bottom, e[i]->getHitbox())) {

                printf("COLLISION GOOMBA CON LOS PIES\n");

                e[i]->state = 0;
                jump(8.0f);
            }
            else {

                printf("COLISION CON GOOMBA\n");

                state--;
                if (state == 0) {
                    // Mario muere
                }
                else {
                    immunity = true;
                }
            }
        }
    }
}
