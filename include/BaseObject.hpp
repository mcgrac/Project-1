#pragma once
#include"raylib.h"
#include"Entity.hpp"


//class Star;
//class Mushroom;
//class Flower;

class BaseObject : public Entity {

protected:

	int typePower; //1 -> mushroom, 2->flower, 3->star, 4->coin

	bool touched = false;
	bool emerging = false; // Al principio está saliendo del bloque
	float emergeSpeed = 0.7f;
	float emergedSoFar;
	float maxEmerge = 16.0f;

public:

	BaseObject(float x, float y, float width, float height, int id, int state,int typePower_);

	virtual void throwPower(){} //used to pop up all the power ups

	//getter
	int getTypePowerUp() { return typePower; }
	bool getTouched() { return touched; }
};
