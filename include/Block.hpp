
#include "raylib.h"


class Block : public Entity {

public:

	//Rectangle block;
	Color color = RED;

	Block() {}
	Block(float x, float y, float width, float heigh, int id, int state) : Entity(x, y, width, heigh, id, state){}


};
