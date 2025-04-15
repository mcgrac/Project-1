#include "GameManager.hpp"


GameManager::GameManager(int screen, int op_, bool drawed_)
    : titleScreen(screen), op(op_), mapDrawed(drawed_) {

    backgroundTexture = LoadTexture("resources/Background.png");
    Title_screenTexture = LoadTexture("resources/Title_screen.png");
    Game_overTexture = LoadTexture("resources/game_over.png");
    StrtTexture = LoadTexture("resources/strt.png");
    Initial_screenTexture = LoadTexture("resources/Initial_screen.png");
    howToPlayTexture1 = LoadTexture("resources/howToPlay.png");
    howToPlayTexture2 = LoadTexture("resources/howToPlay2.png");
    winTexture = LoadTexture("resources/tyMario.png");
    looseTexture = LoadTexture("resources/game_over.png");
    arrowTexture = LoadTexture("resources/arrow.png");

    //sounds
    levelS = LoadSound("resources/audio/GroundTheme.wav");
    gameOverS = LoadSound("resources/audio/GameOver.wav");
    winS = LoadSound("resources/audio/LevelComplete.wav");
}

GameManager::~GameManager() {
    UnloadTexture(backgroundTexture);
    UnloadTexture(Title_screenTexture);
    UnloadTexture(Game_overTexture);
    UnloadTexture(StrtTexture);
    UnloadTexture(Initial_screenTexture);
    UnloadTexture(howToPlayTexture1);
    UnloadTexture(howToPlayTexture2);
    UnloadTexture(winTexture);
    UnloadTexture(arrowTexture);
    UnloadTexture(looseTexture);

    UnloadSound(levelS);
    UnloadSound(gameOverS);
    UnloadSound(winS);
}

void GameManager::mapCreated() {
    mapDrawed = true;
}

bool GameManager::getMapCreated() {
    return mapDrawed;
}

int GameManager::GetScreen() {
    return titleScreen;
}

int GameManager::getOp() {
    return op;
}

void GameManager::setScreen(int titleScreen) {
    this->titleScreen = titleScreen;
}

void GameManager::drawArrow() {
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

void GameManager::opUp() {
    if (op > 0) {
        op--;
    }
}

void GameManager::opDown() {
    if (op < 2) {
        op++;
    }
}

void GameManager::opSelector() {
    if (IsKeyPressed(KEY_PAGE_DOWN)) {
        opDown();
    }
    else if (IsKeyPressed(KEY_PAGE_UP)) {
        opUp();
    }
}

void GameManager::nextScreen() {
    if (titleScreen == 1) {
        titleScreen = 2;
    }
    else if (titleScreen == 2 && op == 0) {
        titleScreen = 3;
    }
    else if (titleScreen == 2 && op == 1) {
        titleScreen = 6;
    }
    else if (titleScreen == 2 && op == 2) {
        CloseWindow();
    }
    else if (titleScreen == 3) {
        titleScreen = 0;
    }
    else if (titleScreen == 4) {
        titleScreen = 2;
        soundPlayedOnce = false;
    }
    else if (titleScreen == 6) {
        titleScreen = 7;
    }
    else if (titleScreen == 7) {
        titleScreen = 2;
    }
    else if (titleScreen == 0) {
        titleScreen = 5;
    }
    else if (titleScreen == 5) {
        titleScreen = 2;
    }
}

void GameManager::gameOver() {
    titleScreen = 4;
}

void GameManager::win() {

    titleScreen = 5;

}

void GameManager::playSounds() {

    switch (titleScreen) {
    case 0: //in-game screen
        if (!IsSoundPlaying(levelS)) {
            PlaySound(levelS);
        }
        break;
    case 1: //title screen
        //DrawTexture(Initial_screenTexture, 0, 0, WHITE);
        break;
    case 2: //main menu screen
        //DrawTexture(Title_screenTexture, 0, 0, WHITE);
        break;
    case 3: //start level screen
        //DrawTexture(StrtTexture, 0, 0, WHITE);
        break;
    case 4: //loose screen

        StopSound(levelS);

        if (!IsSoundPlaying(gameOverS) && !soundPlayedOnce) {
            PlaySound(gameOverS);
            soundPlayedOnce = true;
        }

        
        break;
    case 5: //win screen

        StopSound(levelS);

        if (!IsSoundPlaying(winS) && !soundPlayedOnce) {
            PlaySound(winS);
            soundPlayedOnce = true;
        }

        //DrawTexture(winTexture, 0, 0, WHITE);
        break;
    case 6: //how to play 1 screen
        //DrawTexture(howToPlayTexture1, 0, 0, WHITE);
        break;
    case 7: //how to play 2 screen
        //DrawTexture(howToPlayTexture2, 0, 0, WHITE);
        break;
    default:
        break;
    }

}

void GameManager::drawScreen() {
    switch (titleScreen) {
    case 0: //in-game screen
        DrawTexture(backgroundTexture, 0, -32, WHITE);
        break;
    case 1: //title screen
        DrawTexture(Initial_screenTexture, 0, 0, WHITE);
        break;
    case 2: //main menu screen
        DrawTexture(Title_screenTexture, 0, 0, WHITE);
        break;
    case 3: //start level screen
        DrawTexture(StrtTexture, 0, 0, WHITE);
        break;
    case 4: //loose screen
        DrawTexture(looseTexture, 0, 0, WHITE);
        break;
    case 5: //win screen
        DrawTexture(winTexture, 0, 0, WHITE);
        break;
    case 6: //how to play 1 screen
        DrawTexture(howToPlayTexture1, 0, 0, WHITE);
        break;
    case 7: //how to play 2 screen
        DrawTexture(howToPlayTexture2, 0, 0, WHITE);
        break;
    default:
        break;
    }
}
