
#include "raylib.h"


class Enemy : public Entity {


protected:

	bool alive;

public:

	Enemy(){}
	Enemy(float x, float y, float width, float heigh, int id, bool alive_):Entity(x, y, width, heigh, id), alive(alive_){}

	void die() {


	}
};
