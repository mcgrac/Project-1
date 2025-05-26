#include "Entity.hpp"
#include <vector>

Entity::Entity(float x, float y, float width, float height, int id_, int state_)
    : hitbox{ x, y, width, height }, id(id_), state(state_), toDelete(false) {
}
Entity::~Entity() {};

void Entity::updateRects() { //update the middle points of each side in the hitbox
    top = { hitbox.x + (hitbox.width / 2), hitbox.y };
    left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
    right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
    bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };
}

void Entity::decreaseState() { //decrease when an entity is hitted
    state--;
}

void Entity::markForDelation() {
    toDelete = true;
}
