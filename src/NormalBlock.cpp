#include"NormalBlock.hpp"

NormalBlock::NormalBlock(float x, float y, float width, float heigh, int id, int state, int type_) :Block(x, y, width, heigh, id, state, type_){

	normalBlock = LoadTexture("resources/textures/Block3.png");

	//mushroom = LoadTexture("resources/Block.png");
	updateRects();
}

NormalBlock::~NormalBlock() {};

void NormalBlock::draw() {

	//printf("NORMAL BLOCK DRAW. state: %d\n", state);
	//DrawTexture(normalBlock, hitbox.x, hitbox.y, WHITE);

}

