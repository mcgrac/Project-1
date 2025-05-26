#include "Flag.hpp"

Flag::Flag(float x, float y, float width, float height, int id_, int state_) :Entity(x, y, width, height, id_, state_) {
	flag = LoadTexture("resources/textures/fag.png");
}
Flag::~Flag() {
	UnloadTexture(flag);
}

void Flag::move(float velocity, float delta) {
	hitbox.y += velocity * delta;
}

void Flag::draw() {
	DrawTexture(flag, hitbox.x, hitbox.y, WHITE);
}