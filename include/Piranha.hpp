#pragma once
#include"Enemy.hpp"
#include"raylib.h"

class Piranha : public Enemy {

private:

	Texture2D piranha;
	Texture2D piranha2;

	float timer;
	float piranhaMoved;
	bool moving;
	float movementSpeed;
	float movedSoFar;
	bool goingUp;

public:

	Piranha(float x, float y, float width, float height, int id, int state, char typeEnemy_);
	~Piranha();

	void update(vector<Entity*>& entity, float gravity) override;
	void draw() override;

	bool iterator();

	void shouldMove(float delta);
};
