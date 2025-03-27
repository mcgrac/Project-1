#include "raylib.h"
#include "Entity.hpp"

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
	int state; //0 dead, 1 little, 2 big, 3 powerUp
	//Rectangle grid; //rectangleZonaColision

	//constructor
	Player(float x, float y, float width, float heigh, int id, float speedX, float speedY, float movementSpeed_, int initialState)
		: Entity(x, y, width, heigh, id), speed{ speedX, speedY }, movementSpeed(movementSpeed_), isJumping(false), onGround(false), colliding(false), immunity(false), state(initialState) {
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

	void move(int direction) {

		if (direction == 1) {

			hitbox.x += movementSpeed;
		}
		else {

			hitbox.x -= movementSpeed;
		}

	}

	void colisions(int id) {

		if (id == 1) { //enemy


		}
		else if (id == 2) { //block


		}
	}

	void Immunity(Player& mario) {

		if (mario.immunity) {
			mario.time -= GetFrameTime();
			if (mario.time <= 0) {
				mario.immunity = false;
				mario.time = 3;
			}
		}
	}
};
