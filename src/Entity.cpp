#include "Entity.hpp"
#include <vector>

Entity::Entity(float x, float y, float width, float height, int id_, int state_)
    : hitbox{ x, y, width, height }, id(id_), state(state_) {
    //printf("constructor entity x:%f y:%f\n", hitbox.x, hitbox.y);
}

vector<Entity*> Entity::allEntities;

void Entity::updateRects() {
    top = { hitbox.x + (hitbox.width / 2), hitbox.y };
    left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
    right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
    bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };
}

void Entity::decreaseState() {
    state--;
}

bool Entity::collidingRight( Entity* e) {
    return (hitbox.x < e->hitbox.x) &&
        (hitbox.y <= e->hitbox.y) && (hitbox.y+hitbox.height-3 <= e->hitbox.y);
        
}

bool Entity::collidingLeft( Entity* e) {
    return (hitbox.x > e->hitbox.x)&&(hitbox.y <= e->hitbox.y)&&(hitbox.y + hitbox.height -3 <= e->hitbox.y);
}

bool Entity::collidingBottom( Entity* e) {
    return (bottom.y >= e->top.y) &&
        (bottom.x >= e->left.x) &&
        (bottom.x <= e->right.x);
}

bool Entity::collidingAbove( Entity* e) {
    return (top.y <= e->bottom.y) &&
        (top.y > e->top.y) &&
        (top.x >= e->left.x) &&
        (top.x <= e->right.x);
}
