#pragma once

#include"raylib.h"
#include"BaseObject.hpp"

class Coin : public BaseObject {

private:

	Texture2D coin;

public:

	Coin(float x, float y, float width, float height, int id, int state, int typePower_);

	~Coin();

	void draw() override;
};
