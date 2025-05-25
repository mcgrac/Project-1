#include"Coin.hpp"

Coin::Coin(float x, float y, float width, float height, int id, int state, int typePower_, bool inBlock_, Player* player_) : BaseObject(x, y, width, height, id, state, typePower_), inBlock(inBlock_), player(player_) {

	coin = LoadTexture("resources/textures/coin.png");
	coinSound = LoadSound("resources/audio/smb_coin.wav");
	SetSoundVolume(coinSound, 1.0f);
}

Coin::~Coin() {

	UnloadTexture(coin);
	UnloadSound(coinSound);
}

void Coin::throwPower() {

	emerging = true;
	emergedSoFar = 0.0f;
}

void Coin::update(vector<Entity*>& entity, float gravity) {

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
			PlaySound(coinSound);

			player->addScore(100);

			touched = true;
			toDelete = true;

		}
	}
}

void Coin::draw() {

	DrawTexture(coin, hitbox.x, hitbox.y, WHITE);
}
