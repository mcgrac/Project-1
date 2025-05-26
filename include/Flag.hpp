#pragma once
#include"raylib.h"
#include"Entity.hpp"

class Flag : public Entity {
private:
	Texture2D flag;
public:
	Flag(float x, float y, float width, float height, int id_, int state_);
	~Flag();

	void move(float velocity, float delta);

	void draw() override;
};