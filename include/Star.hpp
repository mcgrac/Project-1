#pragma once
#include"raylib.h"
#include "BaseObject.hpp"

//class GameManager;

class Star : public BaseObject {

private:

	Texture2D star;
	Texture2D star2;

	Vector2 velocity{ 60.0f,0 };
	const float terminalVelocityY = 500.0f;

protected:

public:

	Star(float x, float y, float width, float height, int id, int state, int typePower_);
	~Star();

	void throwPower() override;

	void update(vector<Entity*>& entity, float gravity) override;
	void draw() override;

	void handleCollision();
};
