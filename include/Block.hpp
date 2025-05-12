
#pragma once

#include "raylib.h"
#include "Entity.hpp"

class Block : public Entity {
private:
	Texture2D breakBlock;
	Texture2D block;
	Texture2D surpriseBlock;
	Texture2D floorBlock;

protected:
	int type; // 1-normal block, 2-surprise block, 3B-breakBlock

public:
	Block(float x, float y, float width, float heigh, int id, int state, int type_);
	~Block();
	
};

