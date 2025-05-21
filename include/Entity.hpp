
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "raylib.h"
#include<vector>
using namespace std;

class Entity {
protected:

	//Hitbox of each entity and its middle points of each side
	Rectangle hitbox;
	Vector2 top;
	Vector2 left;
	Vector2 right;
	Vector2 bottom;

	////create a vector that will contain all the entities
	//static vector<Entity*> allEntities;

	int id;     // 0 player, 1 enemy, 2 block, 3 powerUp, 4 Fireballs
	int state;  // 0 dead, 1 little mario, 2 big mario, 3 power up mario
	bool toDelete; //for deleting entities

public:


	Entity(float x, float y, float width, float height, int id_, int state_);
	~Entity();

	virtual void draw() {}; //this will be overwritten in every class of every object to draw it's sprites
	virtual void update(vector<Entity*>& entities, float gravity) {};

	void markForDelation();
	void updateRects(); //update position of the hitbox
	void decreaseState(); //used when a block is hitted, a goomba is hitted or mario is damaged


#pragma region GETTERS
	// Getters
	Rectangle getHitbox() const { return hitbox; }
	Vector2 getTop() const { return top; }
	Vector2 getLeft() const { return left; }
	Vector2 getRight() const { return right; }
	Vector2 getBottom() const { return bottom; }
	int getId() { return id; }
	int getState() { return state; }
	//static vector<Entity*>& getAllEntities() {
	//	return allEntities;
	//}
	bool getToDelate() { return toDelete; }
#pragma endregion
};
#endif
