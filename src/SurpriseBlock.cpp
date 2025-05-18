#include"SurpriseBlock.hpp"
#include"BaseObject.hpp"

SurpriseBlock::SurpriseBlock(float x, float y, float width, float heigh, int id, int state, int type_):Block(x, y, width, heigh, id, state, type_), powerGiven(false){

	surpriseTexture = LoadTexture("resources/textures/mBlock.png");
	surpriseTextureEmpty = LoadTexture("resources/textures/mBlock2.png");

	//mushroom = LoadTexture("resources/Block.png");
	updateRects();
}

SurpriseBlock::~SurpriseBlock() {};

void SurpriseBlock::givePowerUp() {

	powerGiven = true;
}

void SurpriseBlock::getPowerUp(BaseObject* b) {

	powerUpStored = b;
}
void SurpriseBlock::draw() {

	//printf("SURPRISE BLOCK DRAW.  state: %d\n", state);

	if (state == 1) { //if it has not been hitted

		DrawTexture(surpriseTexture, hitbox.x, hitbox.y, WHITE);
	}
	else { //if it has been hitted

		
		DrawTexture(surpriseTextureEmpty, hitbox.x, hitbox.y, WHITE);

		if (!powerGiven) {

			givePowerUp();
		}
	}
}
