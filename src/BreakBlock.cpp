#include "BreakBlock.hpp"

BreakBlock::BreakBlock(float x, float y, float width, float heigh, int id, int state, int type_)
    : Block(x, y, width, heigh, id, state, type_)
{
    break1 = LoadTexture("resources/textures/break_block1.png");
    break2 = LoadTexture("resources/textures/break_block2.png");
    breakBlock = LoadTexture("resources/textures/Block.png");
    breakSound = LoadSound("resources/audio/smb_breakblock.wav");
    SetSoundVolume(breakSound, 1.0f);
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

void BreakBlock::animation(float delta) {
    if (!breaking) {
        breaking = true;
        breakTimer = 0.0f;
        breakStage = 0;
        PlaySound(breakSound);
    }
    else {
        breakTimer += delta;
        if (breakStage == 0 && breakTimer >= 0.1f) {
            breakStage = 1;
            breakTimer = 0.0f;
        }
        else if (breakStage == 1 && breakTimer >= 0.1f) {
            markForDelation();
            UnloadSound(breakSound);
            UnloadTexture(breakBlock);
            UnloadTexture(break1);
            UnloadTexture(break2);
        }
    }
}

void BreakBlock::update(std::vector<Entity*>& entities, float gravity) {
    float delta = GetFrameTime();
    if (markedForDeletion || breaking) {
        animation(delta);
    }
}
