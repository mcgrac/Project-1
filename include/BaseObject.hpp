#include"raylib.h"
#include"Entity.hpp"

class BaseObject : public Entity {

private:


protected:

	int typePower; //0 -> mushroom, 1->flower, 2->star

	bool emerging = true; // Al principio está saliendo del bloque
	float emergeSpeed = 0.7f;
	float emergedSoFar;
	float maxEmerge = 16.0f;

public:

	BaseObject(float x, float y, float width, float height, int id, int state,int typePower_);


	virtual void throwPower(){} //used to pop up all the power ups

	//getter
	int getTypePowerUp() { return typePower; }
};
