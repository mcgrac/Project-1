#pragma once
#include "raylib.h"
#include "Block.hpp"

class NormalBlock :public Block {

private:

	Texture2D normalBlock;

public:

	NormalBlock(float x, float y, float width, float heigh, int id, int state, int type_);

	void draw() override;
};
