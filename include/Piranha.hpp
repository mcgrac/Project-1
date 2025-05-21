#pragma once
#include"Enemy.hpp"
#include"raylib.h"

class Piranha : public Enemy {

private:

	Texture2D piranha;
	float timer;
	float piranhaMoved;
	bool moving;
	float movementSpeed;
	float movedSoFar;
	bool goingUp;

public:

	Piranha(float x, float y, float width, float height, int id, int state);
	~Piranha();

	void update(vector<Entity*>& entity, float gravity) override;
	void draw() override;

	void shouldMove(float delta);
};
