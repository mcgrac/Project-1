#include "raylib.h"
#include "Block.hpp"
#include <vector>

class BreakBlock :public Block {
private:

	Texture2D breakBlock;

public:

	//BreakBlock() {}
	BreakBlock(float x, float y, float width, float heigh, int id, int state, int type) : Block(x, y, width, heigh, id, state, type) {

		breakBlock = LoadTexture("resources/textures/Block2.png");
	}

};
