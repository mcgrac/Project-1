#pragma once
#include"Entity.hpp"
#include"raylib.h"

class Pipe :public Entity {

private:
	Texture2D pipe;
public:

	Pipe(float x, float y, float width, float height, int id, int state);
	~Pipe();

	void draw() override;
};
