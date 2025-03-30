
#include "raylib.h"


class Enemy : public Entity {


protected:



public:

	Enemy(){}
	Enemy(float x, float y, float width, float heigh, int id, int state):Entity(x, y, width, heigh, id, state){}

	//void die() {

	//	alive = false;
	//}

	//bool getAlive() {

	//	return alive;
	//}
};
