#pragma once

#include"raylib.h"
#include"BaseObject.hpp"

class Coin : public BaseObject {

private:

	Texture2D coin;
	bool inBlock;

public:

	Coin(float x, float y, float width, float height, int id, int state, int typePower_, bool inblock_);

	~Coin();

	void draw() override;

	void throwPower() override;

	void update();
	void emerge();
};
