#pragma once
#include "raylib.h"
#include "Block.hpp"

class SurpriseBlock :public  Block{

private:

	Texture2D surpriseTexture;
	Texture2D surpriseTextureEmpty;

	//Texture2D mushroom;

	//int typePower; // 1-mushroom, 2-flower, 3-star
	bool powerGiven;

public:

	SurpriseBlock(float x, float y, float width, float heigh, int id, int state, int type_);
	~SurpriseBlock();

	void givePowerUp();

	void draw() override;
};
