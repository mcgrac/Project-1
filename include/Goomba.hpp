#include "raylib.h"
#include <vector>

class Goomba : public Enemy {

protected:

	float movementSpeed;
	int direction;

public:

	Goomba(){}
	Goomba(float x, float y, float width, float heigh, int id, int state, float movementSpeed_, int direction_) : Enemy(x, y, width, heigh, id, state), movementSpeed(movementSpeed_), direction(direction_){}

	float getMovementSpeed() {

		return movementSpeed;
	}

	void moveGoomba(vector<Entity> entity) {



		//gravity
		hitbox.y += movementSpeed;

		//lateral movement

		//printf("Direction: %d\n", direction);

		if (direction == 1) {

			hitbox.x += (movementSpeed - 4);
		}
		else {

			hitbox.x -= (movementSpeed - 4);
		}

		for (int i = 0; i < entity.size(); ++i) {

			if (entity[i].id == 2 && CheckCollisionRecs(hitbox, entity[i].hitbox)) { //block

				if (CheckCollisionPointRec(bottom, entity[i].hitbox)) {

					//printf("colision bottom\n");

					hitbox.y = entity[i].hitbox.y - hitbox.height;
				}

				if (CheckCollisionPointRec(right, entity[i].hitbox) && direction == 1) { //right

					direction = -1;
				}
				
				if (CheckCollisionPointRec(left, entity[i].hitbox) && direction == -1) { //left

					direction = 1;
				}

				//if (Collidingbottom(entity[i])) {

				//	hitbox.y = entity[i].hitbox.y - hitbox.height;
				//}

				/*if (CollidingAbove(entity[i])) {



				}*/
			}
		}


	}

	void colisionsGoomba(vector<Entity> e) {

		for (int i = 0; i < e.size(); ++i) {

			//if (CheckCollisionRecs(hitbox, e[i].hitbox)) {

			//	if (e[i].id == 2) { //block

			//		hitbox.y = e[i].hitbox.y - hitbox.height;

			//	}
			//}

			if (CheckCollisionPointRec(bottom, e[i].hitbox)) {

				if (e[i].id == 2) { //block

					hitbox.y = e[i].hitbox.y - hitbox.height;

				}
			}
		}
	}
};
