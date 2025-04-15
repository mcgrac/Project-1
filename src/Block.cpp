#include "Block.hpp"
#include <cstdio> // para printf

Block::Block(float x, float y, float width, float heigh, int id, int state, int type_)
    : Entity(x, y, width, heigh, id, state), type(type_) {

    breakBlock = LoadTexture("resources/Block2.png");
    block = LoadTexture("resources/Block3.png");
    //goomba1 = LoadTexture("resources/Goomba1.png");

    allEntities.push_back(this);

    printf("Constructor Block: x = %f, y = %f\n", x, y);
}

Block::~Block() {

    UnloadTexture(breakBlock);
    UnloadTexture(block);
    UnloadTexture(breakBlock);
}

void Block::draw() {

    if (type == 1) {

        //printf("DrawBreakBlock in x: %f and y: %f\n", hitbox.x, hitbox.y);

        DrawTexture(block, hitbox.x, hitbox.y, WHITE);

        //DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
        printf("\n");
    }
    else if (type == 2) {
        // Aquí iría el dibujo del bloque sorpresa si se activa
        // Ej: DrawTexture(surprise, hitbox.x, hitbox.y, WHITE);
    }
}
