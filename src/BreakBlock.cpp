#include "BreakBlock.hpp"

BreakBlock::BreakBlock(float x, float y, float width, float heigh, int id, int state, int type_, bool breaking_, float breakTime_, int breakStage_) : Block(x, y, width, heigh, id, state, type_), breaking(breaking_), breakTimer(breakTime_), breakStage(breakStage_) {

    break1 = LoadTexture("resources/textures/break_block1.png");
    break2 = LoadTexture("resources/textures/break_block2.png");
    breakBlock = LoadTexture("resources/textures/Block.png");
    breakSound = LoadSound("resources/audio/smb_breakblock.wav");
    SetSoundVolume(breakSound, 1.0f);
}

BreakBlock::~BreakBlock() {
	UnloadTexture(breakBlock);
    UnloadTexture(break1);
    UnloadTexture(break2);
    UnloadSound(breakSound);
}

void BreakBlock::draw() {
    if (breaking) {
        // Draw appropriate animation frame
        if (breakStage == 0) {
            DrawTexture(break1, hitbox.x, hitbox.y, WHITE);
        }
        else if (breakStage == 1) {
            DrawTexture(break2, hitbox.x, hitbox.y, WHITE);
        }
    }
    else {
        DrawTexture(breakBlock, hitbox.x, hitbox.y, WHITE);
    }
}

void BreakBlock::changeBreakBlock() {
    PlaySound(breakSound);
    breaking = true;
}

void BreakBlock::animation(float delta) {

    breakTimer += delta;
    if (breakStage == 0 && breakTimer >= 0.1f) {
        breakStage = 1;
        breakTimer = 0.0f;
    }
    else if (breakStage == 1 && breakTimer >= 0.1f) {
        markForDelation();
    }
}

void BreakBlock::update(std::vector<Entity*>& entities, float gravity) {
    float delta = GetFrameTime();
    if (breaking) {
        animation(delta);
    }
}