#pragma once

#include"raylib.h"
#include"BaseObject.hpp"
#include"Player.hpp"

class Coin : public BaseObject {

private:

	Texture2D coin;
	bool inBlock;
	Player* player;
	Sound coinSound;

public:

	Coin(float x, float y, float width, float height, int id, int state, int typePower_, bool inblock_, Player* player_);

	~Coin();

	void draw() override;

	void throwPower() override;

	void update(vector<Entity*>& entity, float gravity) override;
	void emerge();
};
