#include "raylib.h"
#include "Block.hpp"
#include <vector>

class BreakBlock :public Block {
private:

	Texture2D breakBlock;

public:

	BreakBlock(float x, float y, float width, float heigh, int id, int state, int type_);
	void draw() override;
};
