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
#include "Block.hpp"
#include "Goomba.hpp"
#include "GameManager.hpp"
#include "SurpriseBlock.hpp"
#include"NormalBlock.hpp"
#include "PowerUp.hpp"
#include"GameCamera.hpp"

using namespace std;

#define GRAVITY  0.5f    // GRAVITY IN EACH FRAME
#define JUMP_FORCE 8.0f // JUMP FORCE
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

	GameManager gm(1, 0, false); //create a game manager for controlling the game flow
	Player* mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 1, 0, 0, 5.0f, 1); //create Mario
	GameCamera camera(screenWidth, 0, 1952); //create the camera

	// game loop
	while (!WindowShouldClose())// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		gm.playSounds(); //this will call all the sounds

		if (mario->getHitbox().x >= 1000) { //If mario arrives to the end of the level

			gm.win(); //call win function

			//this will delete mario and liberate it's memory and replace it with another mario with the values reseted
			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 1, 0, 0, 5.0f, 1);

			gm.die(); //for the game manager to know that the level has ended and another new level could be started
			camera.reset(); //reset camera position
		}

		if (mario->getState() == 0) { //If mario dies

			gm.gameOver(); //call game over function

			//this will delete mario and liberate it's memory and replace it with another mario with the values reseted
			delete mario;
			mario = new Player(300.0f, 100.0f, TILE_SIZE, TILE_SIZE, 0, 1, 0, 0, 5.0f, 1);

			gm.die(); //for the game manager to know that the level has ended and another new level could be started
			camera.reset(); //reset camera position
		}

		//Go to the next screen
		if (IsKeyPressed(KEY_N)) {
			gm.nextScreen();
		}

		if (gm.GetScreen() == 2) { // for choosing an option in the main menu

			gm.opSelector();
		}

		//--------------------------//
		//---------GAME LOGIC-------// Apply only when we are in the game screen [0]
		//--------------------------//

		if (gm.GetScreen() == 0) {

			//restart the level and build again all the blocks and the enemies
			if (!gm.getlevelStarted()) {

				gm.startLevel(Entity::getAllEntities());
				gm.mapCreated();
			}

			//-----MARIO CONTROLS--------//
			mario->applyGravity(GRAVITY);
			mario->updateRects();

			if (IsKeyDown(KEY_RIGHT)) {

				if (mario->getDir() != 1) {

					printf("chage direction to right");

					mario->changeDirection();
				}

				if (mario->getDir() == 1) { // if I am going right

					mario->move(1, camera.getRawCamera().target.x); //move to the right
				}
				mario->isWalkingTrue();
			}

			if (IsKeyDown(KEY_LEFT)) {

				if (mario->getDir() == 1) {

					printf("chage direction to left");

					mario->changeDirection();
				}

				if (mario->getDir() != 1) { // if I am going left

					mario->move(-1, camera.getRawCamera().target.x); //move to the left
				}
				mario->isWalkingTrue();
			}


			if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)) {
				printf("key released");

				mario->isWalkingFalse();
			}

			mario->colisionsPlayer(Entity::getAllEntities());

			if (mario->retImmunity()) {

				mario->immunityVoid();
			}

			if (IsKeyPressed(KEY_SPACE) && !mario->retJumping()) {

				mario->jump(JUMP_FORCE);
			}

			//------GOOMBA CONTROLS------//
			for (Entity* e : Entity::getAllEntities()) {

				//do a dynamic cast and getting only the entities that are goombas and access to their functions/also check if it's null for avoiding invalid access in memory
				Goomba* g = dynamic_cast<Goomba*>(e);
				if (g != nullptr) {
					g->updateRects();
					g->moveGoomba(Entity::getAllEntities());
				}
			}

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
			mario->draw();

			//draw all the entities
			for (int i = 0; i < Entity::getAllEntities().size(); ++i) { 

				Entity::getAllEntities()[i]->draw();

			}

		}

		DrawText(TextFormat("Is walking = %d", mario->retIsWalking()), 100, 100, 20, BLACK);

		//end camera mode
		camera.end();

		// end drawing and the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	//finish the audio device
	CloseAudioDevice();

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
