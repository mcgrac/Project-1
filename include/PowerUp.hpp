#pragma once
#include"raylib.h"
#include"Entity.hpp"

class PowerUp : public  Entity{

private:

	Texture2D mushroom;

	Sound powerUpS;
	Sound throwFireballS;

	int typePowerUp; //0->mushroom , 1->flower, 2->star

protected:


public:

	PowerUp(float x, float y, float width, float heigh, int id, int state, int typePower_);
	~PowerUp();

	void draw() override;
	
};

