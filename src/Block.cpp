#include "Block.hpp"
#include <cstdio> // para printf

Block::Block(float x, float y, float width, float heigh, int id, int state, int type_)
    : Entity(x, y, width, heigh, id, state), type(type_) {

    breakBlock = LoadTexture("resources/textures/Block2.png");
    block = LoadTexture("resources/textures/Block3.png");

    printf("Constructor Block: x = %f, y = %f\n", x, y);
}

Block::~Block() {

    UnloadTexture(breakBlock);
    UnloadTexture(block);

}

