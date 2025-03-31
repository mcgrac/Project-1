#include "raylib.h"
#include "Entity.hpp"
#include <vector>

using namespace std;

class Player : public Entity {

private:

	float time = 3.0f;

public:

	//Rectangle rect;  // Rectángulo que representa al personaje
	Vector2 speed;   // Velocidad del personaje
	float movementSpeed; // spped of the movement
	bool isJumping;  // Bandera para saber si está en el aire
	bool onGround;
	bool colliding;
	bool immunity;
	//Rectangle grid; //rectangleZonaColision

	//constructor
	Player(float x, float y, float width, float heigh, int id, int state, float speedX, float speedY, float movementSpeed_)
		: Entity(x, y, width, heigh, id, state), speed{ speedX, speedY }, movementSpeed(movementSpeed_), isJumping(false), onGround(false), colliding(false), immunity(false) {
	}

	//Player(float x, float y, float width, float heigh, float rightPoint_x, float downPoint_y, float speedX, float speedY, float movementSpeed_, int initialState)
	//	: Entity(x, y, width, heigh, rightPoint_x, downPoint_y), speed{ speedX, speedY }, movementSpeed(movementSpeed_), isJumping(false), onGround(false), colliding(false), state(initialState) {
	//}

	void jump(float jumpForce) {

		if (!isJumping) { // Solo permitir el salto si no está en el aire
			speed.y = -jumpForce;
			isJumping = true;
		}

	}

	float getTime() { //only necessary for testing

		return time;

	}

	void move(int direction) {

		if (direction == 1) {

			hitbox.x += movementSpeed;
		}
		else {

			hitbox.x -= movementSpeed;
		}

	}

	void immunityVoid(Player& mario) {

		if (mario.immunity) {
			mario.time -= GetFrameTime();
			if (mario.time <= 0) {
				mario.immunity = false;
				mario.time = 3;
			}
		}
	}

	void colisionsPlayerEnemy(vector<Entity> enemy) {

		for (int i = 0; i < enemy.size(); ++i) {

			if (CheckCollisionRecs(hitbox, enemy[i].hitbox) && enemy[i].id == 1 && !immunity) { //enemies

				printf("COLISION CON GOOMBA\n");

				if (CheckCollisionPointRec(bottom, enemy[i].hitbox)) { //si los pies de mario colisionan con goomba

					enemy[i].state = 0; //goomba muerto
					jump(8.0f); //REVISAR SALTO
				}
				else { //mario pierde una vida

					state--;

					if (state == 0) { //si es mario pequeño, mario muere

						//mario muere

					}
					else {

						immunity = true;
						//mario.immunityVoid(mario);
					}
				}

			}
		}
	}

	void colisionsPlayer(vector<Entity> e) {

		for (int i = 0; i < e.size(); ++i) {

			if (e[i].id == 2 && CheckCollisionRecs(hitbox, e[i].hitbox)) { //block

				if (Collidingbottom(e[i])) {


					//printf("Colisión detectada BOTTOM bloque %d\n", i);

					speed.y = 0;
					hitbox.y = e[i].hitbox.y - hitbox.height; // Asegurar que Mario se quede sobre el bloque
					isJumping = false;

				}

				if (CollidingAbove(e[i])) {

					//printf("Colisión detectada TOP bloque %d\n", i);

					hitbox.y = e[i].hitbox.y + e[i].hitbox.height; // Lo mueve justo debajo del bloque
					speed.y = 1.0f; // Hace que caiga inmediatamente

				}

				if (CheckCollisionPointRec(left, e[i].hitbox)) {

					printf("Colliding left\n");

					hitbox.x = e[i].hitbox.x + e[i].hitbox.width;
				}

				if (CheckCollisionPointRec(right, e[i].hitbox)) {

					printf("Colliding right\n");

					hitbox.x = e[i].hitbox.x - e[i].hitbox.width;
				}
			}


		}
	}


	
};
