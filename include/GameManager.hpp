#include "raylib.h"

class GameManager {
private:

	int titleScreen = 1;
	int op = 0;

public:

	//GameManager(){}

	static GameManager& GetInstance() {
		static GameManager instance;
		return instance;
	}

	int GetScreen() { return titleScreen; }  // Getter público

	void setScreen(int titleScreen) { this->titleScreen = titleScreen; } //not used yet

	void opUp() { if (op < 2) { op++; } }

	void opDown() { if (op > 0) { op--; } }

	// title screen -> credits [1]
	// main menu -> [2]
	// world 1-1 -> [3]
	// morir screen -> [4]
	// ganar screen -> [5]
	// how to play -> [6, 7]
	//game screen->[0]

	void nextScreen() {

		if (titleScreen == 1) { titleScreen = 2; } //credits -> main menu

		else if (titleScreen == 2 && op == 0) { titleScreen = 3; } //main menu-> world screen

		else if (titleScreen == 2 && op == 1) { titleScreen = 6; } //main menu -> how to play 1

		else if (titleScreen == 2 && op == 2) { CloseWindow(); } //main menu -> Exit

		else if (titleScreen == 3) { titleScreen = 0; } //world screen -> play screen

		else if (titleScreen == 6) { titleScreen = 7; } //how to play 1 -> how to play 2

		else if (titleScreen == 7) { titleScreen = 2; } //how to play 2 -> main menu


		else if (titleScreen == 0) { titleScreen = 5; } //game screen -> win screen

		else if (titleScreen == 5) { titleScreen = 2; } //win screen -> main menu

		//else if (titleScreen == 4) { titleScreen = 1; }

	}

	void gameOver() { titleScreen = 4; }

	void drawScreen() {}

};
