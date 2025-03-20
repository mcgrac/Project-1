#include "raylib.h"

class Line {

public:
	Vector2 start;
	Vector2 end;
};


class Entity {

private:

	//The diferent corners of each hitbox
	Vector2 initialPos = { hitbox.x, hitbox.y };
	Vector2 rightUp = { hitbox.x + hitbox.width, hitbox.y };
	Vector2 rightDown = { hitbox.x + hitbox.width, hitbox.y + hitbox.height };
	Vector2 leftDown = { hitbox.x, hitbox.y + hitbox.height };

public:

	Rectangle hitbox;
	
	Entity(){}
	//Entity(float x, float y, float width, float heigh, float initPoint_x, float leftPoint_x, float initPoint_y, float downPoint_y) :
	//	hitbox{ x, y, width, heigh }, initialPos{ initPoint_x, initPoint_y }, rightUp{ leftPoint_x, initPoint_y}, rightDown{ leftPoint_x ,downPoint_y }, leftDown{initPoint_x, downPoint_y } {
	//}

	Entity(float x, float y, float width, float heigh) :
		hitbox{ x, y, width, heigh } {}

	Line line(Vector2 start, Vector2 end) {

		Line line{ start, end };

		return line;
	}

	Vector2 getInitialPos() {

		return initialPos = { hitbox.x, hitbox.y };
	}


	Vector2 getRightUp() {

		return rightUp = { hitbox.x + hitbox.width, hitbox.y };
	}


	Vector2 getRightDown() {

		return  rightDown = { hitbox.x + hitbox.width, hitbox.y + hitbox.height };
	}


	Vector2 getLeftDown() {

		return leftDown = { hitbox.x, hitbox.y + hitbox.height };
	}
};
