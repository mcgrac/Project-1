
#pragma once

#include "raylib.h"
#include "Entity.hpp"

class Block : public Entity {
protected:
	int type; // 1-normal block (invisible), 2-surprise block, 3B-breakBlock

public:

	Block(float x, float y, float width, float heigh, int id, int state, int type_);
	~Block() = default;
	
};

