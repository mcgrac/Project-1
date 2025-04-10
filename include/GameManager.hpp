#include "raylib.h"

class GameManager {
private:

	int titleScreen; // 1
	int op; // 0
	bool mapDrawed;

	//screens
	Texture2D backgroundTexture;
	Texture2D Title_screenTexture;
	Texture2D Game_overTexture;
	Texture2D StrtTexture;
	Texture2D Initial_screenTexture;
	Texture2D howToPlayTexture1;
	Texture2D howToPlayTexture2;
	Texture2D winTexture;

	//arrow
	Texture2D arrowTexture;

public:

	GameManager(int screen, int op_, bool drawed_):titleScreen(screen), op(op_), mapDrawed(drawed_){
	
		//Screens
		backgroundTexture = LoadTexture("resources/Background.png");
		Title_screenTexture = LoadTexture("resources/Title_screen.png");
		Game_overTexture = LoadTexture("resources/game_over.png");
		StrtTexture = LoadTexture("resources/strt.png");
		Initial_screenTexture = LoadTexture("resources/Initial_screen.png");
		howToPlayTexture1 = LoadTexture("resources/howToPlay.png");
		howToPlayTexture2 = LoadTexture("resources/howToPlay2.png");
		winTexture = LoadTexture("resources/tyMario.png");

		
		//arrow
		arrowTexture = LoadTexture("resources/arrow.png");
	}

	void mapCreated() {

		mapDrawed = true;
	}

	bool getMapCreated() {

		return mapDrawed;
	}

	int GetScreen() { return titleScreen; }  // Getter público

	int getOp() {

		return op;
	}

	void setScreen(int titleScreen) { this->titleScreen = titleScreen; } //not used yet

	void drawArrow() {

		
		if (op == 0) {

			DrawTexture(arrowTexture, 100, 257, WHITE);
		}
		else if (op == 1) {

			DrawTexture(arrowTexture, 100, 295, WHITE);

		}
		else if (op == 2) {

			DrawTexture(arrowTexture, 100, 335, WHITE);

		}
		
	}

	void opUp() { 
		
		if (op > 0) {

			op--; 
		
		} 
	
	}

	void opDown() { 

		if (op < 2) {

			op++; 
		} 
	}

	void opSelector() {

		if (IsKeyPressed(KEY_PAGE_DOWN)) {

			opDown();
		}
		else if (IsKeyPressed(KEY_PAGE_UP)) {

			opUp();
		}
	}

	// title screen -> credits [1]
	// main menu -> [2]
	// world 1-1 -> [3]
	// morir screen -> [4]
	// ganar screen -> [5]
	// how to play -> [6, 7]
	//game screen->[0]

	void nextScreen() {

		if (titleScreen == 1) { 
			
			titleScreen = 2; 
			
		
		} //credits -> main menu

		else if (titleScreen == 2 && op == 0) { 

			titleScreen = 3;
			
		} //main menu-> world screen

		else if (titleScreen == 2 && op == 1) { 
			titleScreen = 6;
			
		} //main menu -> how to play 1

		else if (titleScreen == 2 && op == 2) {
			CloseWindow(); 
		} //main menu -> Exit

		else if (titleScreen == 3) {
			titleScreen = 0;
			
		} //world screen -> play screen

		else if (titleScreen == 6) {
			titleScreen = 7;
			
		} //how to play 1 -> how to play 2

		else if (titleScreen == 7) {
			titleScreen = 2;
			
		} //how to play 2 -> main menu


		else if (titleScreen == 0) {
			titleScreen = 5;
			
		} //game screen -> win screen

		else if (titleScreen == 5) {
			titleScreen = 2;
			
		} //win screen -> main menu

		//else if (titleScreen == 4) { titleScreen = 1; }

	}

	void gameOver() { titleScreen = 4; }

	void drawScreen() {

		if (titleScreen == 1) {

			DrawTexture(Initial_screenTexture, 0, 0, WHITE);
		}
		else if (titleScreen == 2) {

			DrawTexture(Title_screenTexture, 0, 0, WHITE);

		}
		else if (titleScreen == 3) {

			DrawTexture(StrtTexture, 0, 0, WHITE);

		}
		else if (titleScreen == 4) {



		}
		else if (titleScreen == 5) {

			DrawTexture(winTexture, 0, 0, WHITE);

		}
		else if (titleScreen == 6) {

			DrawTexture(howToPlayTexture1, 0, 0, WHITE);

		}
		else if (titleScreen == 7) {

			DrawTexture(howToPlayTexture2, 0, 0, WHITE);

		}
		else if (titleScreen == 0) {

			DrawTexture(backgroundTexture, 0, 0, WHITE);

		}
	
	
	
	}

};
