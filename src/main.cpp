/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <vector>

#include "raylib.h"
#include "resource_dir.h"	
#include "Player.hpp"
#include "GameManager.hpp"
#include"GameCamera.hpp"

using namespace std;

#define GRAVITY  1000.0f    // GRAVITY IN EACH FRAME
#define TILE_SIZE 16.0f  // MINIMUM TILE SIZE

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	//define the width and height of the screen
	const int screenWidth = 512;
	const int screenHeight = 448;

	InitWindow(screenWidth, screenHeight, "Super MarioBros"); //Initialize the screen
	InitAudioDevice(); //Initialize audio device for the sounds

	GameCamera camera(screenWidth, 0, 3584); //create the camera
	Player* mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE * 2, 0, 2, 0, 0, 200.0f, 1, 0, &camera); //create Mario
	GameManager gm(1, 0, mario); //create a game manager for controlling the game flow

	// game loop
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		gm.playSounds(); //this will call all the sounds

		//if (mario->getHitbox().x >= 3300) { //If mario arrives to the end of the level

		//	gm.win(); //call win function

		//	//this will delete mario and liberate it's memory and replace it with another mario with the values reseted
		//	delete mario;
		//	mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE * 2, 0, 2, 0, 0, 200.0f, 1, 0, &camera);

		//	gm.die(); //for the game manager to know that the level has ended and another new level could be started
		//	camera.reset(); //reset camera position
		//}
		if (mario->getFlagAnimation() && ((mario->getHitbox().y >= 352.0f && (mario->getState() == 3 || mario->getState() == 2)) || (mario->getHitbox().y >= 384.0f && mario->getState() == 1))) { //If mario arrives to the end of the level

			gm.win(); //call win function

			//this will delete mario and liberate it's memory and replace it with another mario with the values reseted
			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE * 2, 0, 2, 0, 0, 200.0f, 1, 0, &camera);

			gm.die(); //for the game manager to know that the level has ended and another new level could be started
			camera.reset(); //reset camera position
		}


		if (mario->getAlive() == false) { //If mario dies

			gm.gameOver(); //call game over function

			//this will delete mario and liberate it's memory and replace it with another mario with the values reseted
			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE * 2, 0, 2, 0, 0, 200.0f, 1, 0, &camera);

			gm.die(); //for the game manager to know that the level has ended and another new level could be started
			camera.reset(); //reset camera position
		}

		gm.update();
		//Go to the next screen
		//if (IsKeyPressed(KEY_N)) {
		//	gm.nextScreen();
		//}

		//if (gm.GetScreen() == 2) { // for choosing an option in the main menu

		//	gm.opSelector();
		//}

		//--------------------------//
		//---------GAME LOGIC-------// Apply only when we are in the game screen [0]
		//--------------------------//

		if (gm.GetScreen() == 0) {

			//restart the level and build again all the blocks and the enemies
			if (!gm.getlevelStarted()) {

				gm.startLevel();

				for (int i = 0; i < gm.getAllEntities().size();i++) {
					printf("Entity id: %d| state: %d\n", gm.getAllEntities()[i]->getId(), gm.getAllEntities()[i]->getState());
				}
				gm.mapCreated();
			}

			//-----MARIO CONTROLS--------//
			mario->update(gm.getAllEntities(), GRAVITY);

			//mario->applyGravity(GRAVITY);
			//mario->updateRects(); //updating the middle points of the hitbox at every moment when it move

			//if (IsKeyDown(KEY_RIGHT)) {

			//	if (mario->getDir() != 1) {

			//		printf("chage direction to right");

			//		mario->changeDirection();
			//	}

			//	if (mario->getDir() == 1) { // if I am going right

			//		mario->move(1, camera.getRawCamera().target.x); //move to the right
			//	}
			//	mario->isWalkingTrue();
			//}

			//if (IsKeyDown(KEY_LEFT)) {

			//	if (mario->getDir() == 1) {

			//		printf("chage direction to left");

			//		mario->changeDirection();
			//	}

			//	if (mario->getDir() != 1) { // if I am going left

			//		mario->move(-1, camera.getRawCamera().target.x); //move to the left
			//	}
			//	mario->isWalkingTrue();
			//}


			//if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)) {
			//	printf("key released");

			//	mario->isWalkingFalse();
			//}

			//mario->colisionsPlayer(gm.getAllEntities());

			//if (mario->retImmunity()) {

			//	mario->immunityVoid();
			//}

			//if (IsKeyPressed(KEY_SPACE) && !mario->retJumping()) {

			//	mario->jump(JUMP_FORCE);
			//}

			//------IA CONTROLS------//
			if (mario->getState() != 0 && !mario->getFlagAnimation()) {
				gm.manageEntities(GRAVITY);
			}
			//for (Entity* e : gm.getAllEntities()) {


			//	//do a dynamic cast and getting only the entities that are goombas and access to their functions/also check if it's null for avoiding invalid access in memory
			//	Goomba* g = dynamic_cast<Goomba*>(e);
			//	if (g != nullptr) {
			//		g->updateRects();
			//		g->moveGoomba(gm.getAllEntities(), GRAVITY);


			//	}

			//	Star* s = dynamic_cast<Star*>(e);
			//	if ( s != nullptr) { //if it is a power up not null
			//		s->update(GRAVITY);
			//	}

			//	Mushroom* m = dynamic_cast<Mushroom*>(e);
			//	if (m != nullptr) { //if it is a power up not null
			//		m->update(GRAVITY);
			//	}

			//	Flower* f = dynamic_cast<Flower*>(e);
			//	if (f != nullptr) {
			//		f->update(GRAVITY);
			//	}

			//	Coin* c = dynamic_cast<Coin*>(e);
			//	if (c != nullptr) {
			//		c->update(GRAVITY);
			//	}
			//}

			//------CAMERA CONTROLS------//
			camera.update(mario->getHitbox());
		}
		
		//-------------------------------------------DRAWING-----------------------------------------------------------//

		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		//draw the corresponding screens
		gm.drawScreen(camera.getRawCamera(), screenWidth, screenHeight);

		//if we are in the main menu draw the arrow for selecting an option
		if (gm.GetScreen() == 2) {

			gm.drawArrow();
		}

		//Draw the in-game characters and scenario and begin the camera mode
		if (gm.GetScreen() == 0) {

			camera.begin();

			//draw all the entities
			for (int i = 0; i < gm.getAllEntities().size(); ++i) { 

				gm.getAllEntities()[i]->draw();

			}

			mario->draw();
		}

		//end camera mode
		camera.end();


		DrawText(TextFormat("Is walking = %d", mario->retIsWalking()), 10, 10, 20, BLACK);
		DrawText(TextFormat("Souns played = %d", gm.retSound()), 10, 30, 20, BLACK);
		DrawText(TextFormat("Score: %d", mario->getScorePlayer()), 10, 50, 20, BLACK);
		DrawText(TextFormat("Direction: %d", mario->getDir()), 10, 70, 20, BLACK);
		

		// end drawing and the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	//finish the audio device
	CloseAudioDevice();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
