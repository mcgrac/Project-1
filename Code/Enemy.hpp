
#include "raylib.h"
#include "Entity.hpp"

class Enemy : public Entity {

private:


protected:

	bool alive;

public:

	Enemy(){}
	Enemy(float x, float y, float width, float heigh, int id, bool alive_):Entity(x, y, width, heigh, id), alive(alive_){}

	void die() {


	}
};
