
#include "raylib.h"
#include <math.h> 

class Entity {


//private:

	//The diferent corners of each hitbox
	//Vector2 initialPos = { hitbox.x, hitbox.y };
	//Vector2 rightUp = { hitbox.x + hitbox.width, hitbox.y };
	//Vector2 rightDown = { hitbox.x + hitbox.width, hitbox.y + hitbox.height };
	//Vector2 leftDown = { hitbox.x, hitbox.y + hitbox.height };

	//Vector2 initialPos;
	//Vector2 rightUp;
	//Vector2 rightDown;
	//Vector2 leftDown;

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

	Entity() {}
	Entity(float x, float y, float width, float heigh, int id_) :
		hitbox{ x, y, width, heigh }, id(id_) {
	}

	//Entity(float x, float y, float width, float heigh, float rightPoint_x, float downPoint_y) :
	//	hitbox{ x, y, width, heigh }, initialPos{ x, y }, rightUp{ rightPoint_x, y }, rightDown{ rightPoint_x ,downPoint_y }, leftDown{ x, downPoint_y } {
	//}

	//Entity(float x, float y, float width, float heigh) :
	//	hitbox{ x, y, width, heigh } {}

	//Line line(Vector2 start, Vector2 end) {

	//	Line line{ start, end };

	//	return line;
	//}

	void updateRects() {

		top = { hitbox.x + (hitbox.width / 2), hitbox.y };
		left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
		right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
		bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };
	}

	float distancePoints(Vector2 p1, Vector2 p2) {

		return sqrtf(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
	}

	//void colisions(int id) {

	//	if (id == 1) { //enemy


	//	}
	//	else if (id == 2) { //block


	//	}
	//}

	/*Vector2 getInitialPos() {

		return initialPos;
	}

	Vector2 getRightUp() {
		return rightUp;
	}

	Vector2 getRightDown() {
		return  rightDown;
	}

	Vector2 getLeftDown() {
		return leftDown;
	}*/
};

