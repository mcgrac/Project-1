
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include<vector>
using namespace std;

class Entity {
protected:
	Rectangle hitbox;
	Vector2 top;
	Vector2 left;
	Vector2 right;
	Vector2 bottom;
	Vector2 leftBot;
	Vector2 rightBot;

	static vector<Entity*> allEntities;

	bool toDelate = false;
	
public:
	int id;     // 0 player, 1 enemy, 2 block, 3 powerUp
	int state;  // 0 dead, 1 little mario, 2 big mario, 3 power up mario

	Entity(float x, float y, float width, float height, int id_, int state_);
	virtual void draw() {};

	void updateRects();
	float distancePoints(Vector2 p1, Vector2 p2);

	bool collidingRight( Entity& e);
	bool collidingLeft( Entity& e);
	bool collidingBottom( Entity* e);
	bool collidingAbove( Entity* e);

	// Getters
	Rectangle getHitbox() const { return hitbox; }
	Vector2 getTop() const { return top; }
	Vector2 getLeft() const { return left; }
	Vector2 getRight() const { return right; }
	Vector2 getBottom() const { return bottom; }
	static vector<Entity*>& getAllEntities() {
		return allEntities;
	}
	bool changeToDelate() { return !toDelate; }
	bool retToDelate() { return toDelate; }
};
#endif

