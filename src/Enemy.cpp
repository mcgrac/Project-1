#include "Enemy.hpp"

Enemy::Enemy(float x, float y, float width, float height, int id, int state, char typeEnemy_)
    : Entity(x, y, width, height, id, state), typeEnemy(typeEnemy_) {}

Enemy:: ~Enemy() {};
