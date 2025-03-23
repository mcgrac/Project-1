#include "raylib.h"

class Block: public Entity {

public:

	//Rectangle block;
	Color color;

	Block(){}
	Block(float x, float y, float width, float heigh, Color color_): Entity(x, y, width, heigh), color{color_} {}


};
