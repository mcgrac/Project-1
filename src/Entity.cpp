#include "Entity.hpp"
#include <cmath>
#include <cstdio>

Entity::Entity(float x, float y, float width, float height, int id_, int state_)
    : hitbox{ x, y, width, height }, id(id_), state(state_) {
    printf("constructor entity x:%f y:%f\n", hitbox.x, hitbox.y);
    updateRects();
}

vector<Entity*> Entity::allEntities;

void Entity::updateRects() {
    top = { hitbox.x + (hitbox.width / 2), hitbox.y };
    left = { hitbox.x, hitbox.y + (hitbox.height / 2) };
    right = { hitbox.x + hitbox.width, hitbox.y + (hitbox.height / 2) };
    bottom = { hitbox.x + (hitbox.width / 2), hitbox.y + hitbox.height };
    leftBot = { hitbox.x + 3, hitbox.y + hitbox.height };
    rightBot = { hitbox.x + hitbox.width - 3, hitbox.y + hitbox.height };
}

float Entity::distancePoints(Vector2 p1, Vector2 p2) {
    return sqrtf(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

bool Entity::collidingRight( Entity& e) {
    return hitbox.x < e.hitbox.x;
}

bool Entity::collidingLeft( Entity& e) {
    return hitbox.x > e.hitbox.x;
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
