#include "raylib.h"
#include <vector>

class Goomba : public Enemy {

protected:

	float movementSpeed;

public:

	Goomba(){}
	Goomba(float x, float y, float width, float heigh, int id, int state, float movementSpeed_) : Enemy(x, y, width, heigh, id, state), movementSpeed(movementSpeed_){}

	float getMovementSpeed() {

		return movementSpeed;
	}

	void moveGoomba(vector<Entity> entity) {

		//gravity
		hitbox.y += movementSpeed;

		//lateral movement
		int direction = 1; //1 right, -1 left

		//if (direction == 1) {

		//	hitbox.x += (movementSpeed - 4);
		//}
		//else {

		//	hitbox.x -= (movementSpeed - 4);
		//}

		for (int i = 0; i < entity.size(); ++i) {

			if (entity[i].id == 2 && CheckCollisionRecs(hitbox, entity[i].hitbox)) { //block

				if (CheckCollisionPointRec(right, entity[i].hitbox) && direction == 1) { //right

					direction = -1;
				}
				
				if (CheckCollisionPointRec(left, entity[i].hitbox) && direction == -1) { //left

					direction = 1;
				}

				
			}
		}
	}

	void colisionsGoomba(vector<Entity> e) {

		for (int i = 0; i < e.size(); ++i) {

			if (CheckCollisionRecs(hitbox, e[i].hitbox)) {

				if (e[i].id == 2) { //block

					hitbox.y = e[i].hitbox.y - hitbox.height;

				}
			}
		}
	}
};
