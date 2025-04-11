#include "Goomba.hpp"
#include "raylib.h"

Goomba::Goomba(float x, float y, float width, float height, int id, int state, float movementSpeed_, int direction_)
    : Enemy(x, y, width, height, id, state), movementSpeed(movementSpeed_), direction(direction_) {

    goomba1 = LoadTexture("resources/Goomba1.png");
}

Goomba::~Goomba() {

    UnloadTexture(goomba1);

}


float Goomba::getMovementSpeed() {
    return movementSpeed;
}

void Goomba::draw() {
    DrawTexture(goomba1, hitbox.x, hitbox.y, WHITE);
}


void Goomba::moveGoomba(std::vector<Entity*> entity) {
    // gravity
    hitbox.y += movementSpeed;

    // lateral movement
    if (direction == 1) {
        hitbox.x += (movementSpeed - 4);
    }
    else {
        hitbox.x -= (movementSpeed - 4);
    }

    for (int i = 0; i < entity.size(); ++i) {
        if (entity[i]->id == 2 && CheckCollisionRecs(hitbox, entity[i]->getHitbox())) { // block
            if (CheckCollisionPointRec(bottom, entity[i]->getHitbox())) {
                hitbox.y = entity[i]->getHitbox().y - hitbox.height;
            }

            if (CheckCollisionPointRec(right, entity[i]->getHitbox()) && direction == 1) {
                direction = -1;
            }

            if (CheckCollisionPointRec(left, entity[i]->getHitbox()) && direction == -1) {
                direction = 1;
            }
        }
    }
}

void Goomba::colisionsGoomba(std::vector<Entity> e) {
    for (int i = 0; i < e.size(); ++i) {
        if (CheckCollisionPointRec(bottom, e[i].getHitbox())) {
            if (e[i].id == 2) { // block
                hitbox.y = e[i].getHitbox().y - hitbox.height;
            }
        }
    }
}
