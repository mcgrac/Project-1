#include "Block.hpp"
#include <cstdio> // para printf

Block::Block(float x, float y, float width, float heigh, int id, int state, int type_)
    : Entity(x, y, width, heigh, id, state), type(type_) {

    printf("Constructor Block: x = %f, y = %f\n", x, y);
}


