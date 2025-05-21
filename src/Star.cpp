#include"Star.hpp"
#include"GameManager.hpp"


Star::Star(float x, float y, float width, float height, int id, int state, int typePower_) : BaseObject(x, y, width, height, id, state, typePower_){

    star = LoadTexture("resources/textures/star1.png");
    star2 = LoadTexture("resources/textures/star2.png");
}

Star::~Star() {

	UnloadTexture(star);
}

void Star::throwPower() {

	// Esto se llama al momento de "activar" el power-up
	emerging = true;
	emergedSoFar = 0.0f;
	// Puedes resetear valores si quieres reutilizar objetos
}

void Star::update(vector<Entity*>& entity, float gravity) {

    float delta = GetFrameTime();

    if (emerging && !touched) { //start to emerge

        float delta = GetFrameTime();
        float move = emergeSpeed * delta * 60;
        hitbox.y -= move;
        emergedSoFar += move;
        if (emergedSoFar >= maxEmerge) {
            emerging = false;
            touched = true;
        }
    }
    else if (!emerging && touched){
        
        updateRects(); //necesary for updating the mid points of the hitbox

        //movement x-axis
        hitbox.x += velocity.x * delta;
 
        //gravity //movement y-axis
        velocity.y += gravity;
        if (velocity.y > terminalVelocityY) { velocity.y = terminalVelocityY; } //prevents the gravity to be too much high

        hitbox.y += velocity.y * delta;
        //handleCollisionY();

        handleCollision();
    }
}

void Star::handleCollision() {

    const float push = 0.1f;
    for (Entity* ent : GameManager::getAllEntities()) {

        if (ent->getId() != 2) {
            continue;
        }

        Rectangle block = ent->getHitbox();
        if (CheckCollisionRecs(getHitbox(), block)) {

            printf("handling collisions star");

            // Collision with floor (falling)
            if (velocity.y > 0 && CheckCollisionPointRec(bottom, block)) {
                hitbox.y = block.y - hitbox.height;
                velocity.y = -200.0f; // Bounce
            }

            // Collision with the celling
            else if (velocity.y < 0 && CheckCollisionPointRec(top, block)) {
                hitbox.y = block.y + block.height;
                velocity.y = 0.0f;
            }

            // Collision left
            if (velocity.x < 0 && CheckCollisionPointRec(left, block)) {
                hitbox.x = block.x + block.width + push;
                velocity.x *= -1;
            }

            // Collision right
            else if (velocity.x > 0 && CheckCollisionPointRec(right, block)) {
                hitbox.x = block.x - hitbox.width - push;
                velocity.x *= -1;
            }
        }
    }
}

void Star::draw() {

    DrawTexture(star, hitbox.x, hitbox.y, WHITE);
}
