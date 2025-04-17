#include "PowerUp.hpp"
#include <cstdio>
#include<vector>

using namespace std;

PowerUp::PowerUp(float x, float y, float width, float heigh, int id, int state, float movementSpeed_)
	: Entity(x, y, width, heigh, id, state), 
	movementSpeed(movementSpeed_), 
	colliding(false){

	powerUpS = LoadSound("resources/PowerUp.wav");
	throwFireballS = LoadSound("resources/ThrowFireball.wav");
}

//
//float getMovementSpeed() {
//
//	return movementSpeed;
//}

//void moveGoomba(vector<Entity> entity) {
//
//	//gravity
//	hitbox.y += movementSpeed;
//
//	//lateral movement
//	int direction = 1; //1 right, -1 left
//
//	for (int i = 0; i < entity.size(); ++i) {
//
//		if (entity[i].id == 2 && CheckCollisionRecs(hitbox, entity[i].hitbox)) { //block
//
//			if (CheckCollisionPointRec(right, entity[i].hitbox) && direction == 1) { //right
//
//				direction = -1;
//			}
//
//			if (CheckCollisionPointRec(left, entity[i].hitbox) && direction == -1) { //left
//
//				direction = 1;
//			}
//		}
//	}
//}

//void colisionsMushroom(Player& p, vector <Entity> m, vector <Entity> e) {
//
//	for (int i = 0; i < e.size(); ++i) {
//		if (CheckCollisionRecs(hitbox, p.hitbox)) {
//
//			if (p.id == 0) { //mario
//				m[i].state = 0;
//			}
//
//			if (e[i].id == 2) {
//
//				hitbox.y = e[i].hitbox.y - hitbox.height;
//			}
//		}
//	}
//}

PowerUp::~PowerUp() {
	UnloadSound(powerUpS);
	UnloadSound(throwFireballS);
}
