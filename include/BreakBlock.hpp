#pragma once
#include "raylib.h"
#include "Block.hpp"
#include <vector>

class BreakBlock :public Block {
private:

	Texture2D breakBlock;
	Texture2D break1;
	Texture2D break2;
	Sound breakSound;
	bool markedForDeletion = false;

	bool breaking;
	float breakTimer;
	int breakStage;


public:

	BreakBlock(float x, float y, float width, float heigh, int id, int state, int type_, bool breaking_, float breakTime_, int breakStage_);
	~BreakBlock();

	void animation(float delta);
	void draw() override;
	void update(vector<Entity*>& entities, float gravity) override;

	void changeBreakBlock();
};