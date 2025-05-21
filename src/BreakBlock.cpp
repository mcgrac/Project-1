#include "BreakBlock.hpp"

BreakBlock::BreakBlock(float x, float y, float width, float heigh, int id, int state, int type_) : Block(x, y, width, heigh, id, state, type_) {

	breakBlock = LoadTexture("resources/textures/Block.png");
}

void BreakBlock::draw() {

	DrawTexture(breakBlock, hitbox.x, hitbox.y, WHITE);
}
