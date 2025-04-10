
#include "raylib.h"


class Block : public Entity {
private:

	bool mapCreated;
	Texture2D breakBlock;
	Texture surprise;

protected:

	int type; //1-normal block, 2-surprise block

public:


	Block() {}
	Block(float x, float y, float width, float heigh, int id, int state, int type_) : Entity(x, y, width, heigh, id, state), type(type_){

		breakBlock = LoadTexture("resources/Block2.png"); //type 1
		surprise = LoadTexture("resources/Block3.png"); //type surprise (2)
	}

	bool getMapCreated() {

		return mapCreated;
	}

	void drawBlock() {

		if (type == 1) {

			//if it is a block, draw it
			//DrawRectangleRec(entities[i].hitbox, RED);
			DrawTexture(breakBlock, hitbox.x, hitbox.y, WHITE);
		}
		else if (type == 2) {

			DrawTexture(surprise, hitbox.x, hitbox.y, WHITE);
		}
	}

};
