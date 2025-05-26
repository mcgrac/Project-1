#include"Pipe.hpp"

Pipe::Pipe(float x, float y, float width, float height, int id, int state) :Entity(x, y, width, height, id, state) {
	//pipe
	pipe = LoadTexture("resources/textures/Pipe.png");
}

Pipe::~Pipe() {
	UnloadTexture(pipe);
}

void Pipe::draw() {
	DrawTexture(pipe, hitbox.x, hitbox.y, WHITE);
}