#include"Coin.hpp"

Coin::Coin(float x, float y, float width, float height, int id, int state, int typePower_, bool inBlock_) : BaseObject(x, y, width, height, id, state, typePower_), inBlock(inBlock_) {

	coin = LoadTexture("resources/textures/coin.png");
}

Coin::~Coin() {


}

void Coin::throwPower() {

	emerging = true;
	emergedSoFar = 0.0f;
}

void Coin::update() {

	if (inBlock) { //only do the emerging animation if it is contained in a block
		emerge();
	}

	if (!inBlock) { touched = true; } //if its not inside a block it touched needs to be true, otherwise player won't detect the collision
}

void Coin::emerge() {

	float delta = GetFrameTime();

	if (emerging && !touched) {

		float move = delta * emergeSpeed * 60;

		hitbox.y -= move;
		emergedSoFar += move;

		if (emergedSoFar >= maxEmerge) { // if it energe one tile it stops emerging
			emerging = false;
			touched = true;
		}
	}
}

void Coin::draw() {

	DrawTexture(coin, hitbox.x, hitbox.y, WHITE);
}
