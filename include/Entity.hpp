
#include "raylib.h"
#include <math.h> 

class Entity {

protected:

	Vector2 leftBot = { hitbox.x + (hitbox.width - (hitbox.width - 3)), hitbox.y + hitbox.height };
	Vector2 rightBot = { hitbox.x + (hitbox.width - 3), hitbox.y + hitbox.height };

public:

	Rectangle hitbox;
	//float rightPoint_x, downPoint_y;

	//middle points of each side
	Vector2 top = { hitbox.x + (hitbox.width / 2), hitbox.y };
	Vector2 left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
	Vector2 right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
	Vector2 bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };

	int id; //0 player, 1 enemy, 2 block
	int state; //0 dead, 1 little mario or alive, 2 big mario, 3 power up mario

	Entity() {}
	Entity(float x, float y, float width, float heigh, int id_, int state_) :
		hitbox{ x, y, width, heigh }, id(id_), state(state_) {
	}

	//Entity(float x, float y, float width, float heigh, float rightPoint_x, float downPoint_y) :
	//	hitbox{ x, y, width, heigh }, initialPos{ x, y }, rightUp{ rightPoint_x, y }, rightDown{ rightPoint_x ,downPoint_y }, leftDown{ x, downPoint_y } {
	//}

	//Entity(float x, float y, float width, float heigh) :
	//	hitbox{ x, y, width, heigh } {}

	void updateRects() {

		top = { hitbox.x + (hitbox.width / 2), hitbox.y };
		left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
		right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
		bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };
	}

	float distancePoints(Vector2 p1, Vector2 p2) {

		return sqrtf(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
	}

	bool collidingRight(Entity e) {

		return (hitbox.x < e.hitbox.x);
	}

	bool collidingLeft(Entity e) {

		return (hitbox.x > e.hitbox.x);
	}

	bool Collidingbottom(Entity e) {

		return (bottom.y >= e.top.y) &&
			(bottom.x >= e.left.x) &&
			(bottom.x <= e.right.x);
	}

	bool CollidingAbove(Entity e) {

		return (top.y <= e.bottom.y) &&  // Mario está por debajo del bloque
			(top.y > e.top.y) &&  // Mario no está por encima del bloque
			(top.x >= e.left.x) &&  // Mario está dentro del rango horizontal izquierdo
			(top.x <= e.right.x);  // Mario está dentro del rango horizontal derecho
	}

};

