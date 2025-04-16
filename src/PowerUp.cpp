#include"PowerUp.hpp"

PowerUp::PowerUp(float x, float y, float width, float heigh, int id, int state, int typePower_) : Entity(x, y, width, heigh, id, state), typePowerUp(typePower_){

	mushroom = LoadTexture("resources/Block.png");
}

void PowerUp::draw() {


}

