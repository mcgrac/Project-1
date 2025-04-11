
#pragma once

#include "raylib.h"
#include "Entity.hpp"

class Block : public Entity {
private:
	Texture2D breakBlock;
	Texture2D block;
	//Texture2D goomba1;

protected:
	int type; // 1-normal block, 2-surprise block

public:
	Block(float x, float y, float width, float heigh, int id, int state, int type_);
	~Block();
	void draw() override;
};

