#include "Piranha.hpp"

Piranha::Piranha(float x, float y, float width, float height, int id, int state) :Enemy(x, y, width, height, id, state), timer(0.0f), piranhaMoved(0.0f), moving(false), movementSpeed(0.7f), movedSoFar(0.0f), goingUp(false) {

	piranha = LoadTexture("resources/textures/piranha.png");
}
Piranha::~Piranha() {

	UnloadTexture(piranha);
}
void Piranha::update(vector<Entity*>& entity, float gravity) {

	float delta = GetFrameTime();//frame independent

	if (!moving) {
		shouldMove(delta);
	}
	else {

		if (!goingUp && movedSoFar == 0.0f) {
			timer += delta;
			if (timer < 2.0f) {
				return; // still waiting
			}
			// Finishing waiting
			timer = 0.0f;
		}

		float moveStep = movementSpeed * delta * 40.0f;

		if (goingUp) {
			hitbox.y -= moveStep;
		}
		else {
			hitbox.y += moveStep;
		}
		movedSoFar += moveStep;
		

		if (movedSoFar >= 32.0f) { //if it has emerged 32 pixels (2 tiles), reset.
			movedSoFar = 0.0f;
			if (goingUp) { //starts to go down
				goingUp = false;
				timer = 0.0f; 
			}
			else {
				moving = false;  // terminó el ciclo
				timer = 0.0f;    // empieza espera abajo
			}
		}
	}
}

void Piranha::shouldMove(float delta) {

	timer += delta;
	if (timer >= 5.0f) {
		moving = true;
		timer = 0.0f;
		movedSoFar = 0.0f;
		goingUp = true;
	}
}

void Piranha::draw() {
	DrawTexture(piranha, hitbox.x, hitbox.y, WHITE);
}
