#include "raylib.h"


class Goomba : public Enemy {

protected:

	float movementSpeed;

public:

	Goomba(){}
	Goomba(float x, float y, float width, float heigh, int id, bool alive_ , float movementSpeed_) : Enemy(x, y, width, heigh, id, alive_), movementSpeed(movementSpeed_){}

	float getMovementSpeed() {

		return movementSpeed;
	}

	void moveGoomba() {

		//gravity
		hitbox.y += movementSpeed;
	}

	void colisionGoomba(Entity e) {

		if (e.id == 2) { //colisiona con bloque

			hitbox.y = e.hitbox.y - hitbox.height;
		}
		else if (e.id == 0) { // colisiona con player


		}
	}
};
