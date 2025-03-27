#include "raylib.h"
#include "Enemy.hpp"

class Goomba : public Enemy {

private:


protected:


public:

	Goomba(){}
	Goomba(float x, float y, float width, float heigh, int id, bool alive_) : Enemy(x, y, width, heigh, id, alive_){}
};
