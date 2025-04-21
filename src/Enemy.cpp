#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float width, float height, int id, int state)
    : Entity(x, y, width, height, id, state) {}

Enemy:: ~Enemy() {};
