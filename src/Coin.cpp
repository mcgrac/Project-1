#include"Coin.hpp"

Coin::Coin(float x, float y, float width, float height, int id, int state, int typePower_) : BaseObject(x, y, width, height, id, state, typePower_) {

	coin = LoadTexture("resources/textures/coin.png");
}

Coin::~Coin() {


}

void Coin::draw() {

}
