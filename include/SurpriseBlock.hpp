#pragma once
#include "raylib.h"
#include "Block.hpp"

class BaseObject;

class SurpriseBlock :public  Block{

private:

	Texture2D surpriseTexture;
	Texture2D surpriseTextureEmpty;

	//Texture2D mushroom;

	//int typePower; // 1-mushroom, 2-flower, 3-star
	bool powerGiven;

	BaseObject* powerUpStored;

public:

	SurpriseBlock(float x, float y, float width, float heigh, int id, int state, int type_);
	~SurpriseBlock();

	void getPowerUp(BaseObject* b);

	void givePowerUp();

	void draw() override;

	BaseObject* retPowerUp() { return powerUpStored; }
};
