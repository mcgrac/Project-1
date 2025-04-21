#include "GameManager.hpp"


GameManager::GameManager(int screen, int op_)
    : titleScreen(screen), op(op_) {

#pragma region TEXTURES
    backgroundTexture = LoadTexture("resources/textures/Background.png");
    Title_screenTexture = LoadTexture("resources/textures/Title_screen.png");
    Game_overTexture = LoadTexture("resources/textures/game_over.png");
    StrtTexture = LoadTexture("resources/textures/strt.png");
    Initial_screenTexture = LoadTexture("resources/textures/Initial_screen.png");
    howToPlayTexture1 = LoadTexture("resources/textures/howtoplay1.png");
    howToPlayTexture2 = LoadTexture("resources/textures/howtoplay2.png");
    winTexture = LoadTexture("resources/textures/tyMario.png");
    looseTexture = LoadTexture("resources/textures/game_over.png");
    arrowTexture = LoadTexture("resources/textures/arrow.png");
#pragma endregion

#pragma region SOUNDS
    levelS = LoadSound("resources/audio/GroundTheme.wav");
    gameOverS = LoadSound("resources/audio/GameOver.wav");
    winS = LoadSound("resources/audio/LevelComplete.wav");
#pragma endregion
}

GameManager::~GameManager() {

#pragma region TEXTURES
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
#pragma endregion

#pragma region SOUNDS
    UnloadSound(levelS);
    UnloadSound(gameOverS);
    UnloadSound(winS);
#pragma endregion
}

void GameManager::buildLevel(vector<Entity*>& entities, int tileSize_, int rows_, int col_) {
    const int TILE_SIZE = tileSize_;
    int row = rows_;
    int col = col_;

    LoadMapFromFile("resources/assets/map.txt", rows_, col_);

    //traverse all the array
    for (int row = 0; row < 28; ++row) {
        for (int col = 0; col < 100; ++col) {
            int tile = map[row][col];
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;

            //for each tile place the correct block
            switch (tile) {
            case 1:
                entities.push_back(new NormalBlock(x, y, TILE_SIZE, TILE_SIZE, 2, 1, 1));
                break;
            case 2:
                entities.push_back(new SurpriseBlock(x, y, TILE_SIZE, TILE_SIZE, 2, 1, 2));
                break;
            default:
                break;
            }
        }
    }
}

void GameManager:: LoadMapFromFile(const string& filename, int rows, int columns) {

    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de mapa: " << filename << std::endl;
        return;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            file >> map[row][col];
        }
    }

    file.close();
}

void GameManager::createGoomba(vector<Entity*>& entities) {

    Goomba* goomba = new Goomba(400.0f, 200.0f, 16, 16, 1, 1, 5.0f, 1);
    entities.push_back(goomba);

    Goomba* goomba2 = new Goomba(500.0f, 200.0f, 16, 16, 1, 1, 5.0f, -1);
    entities.push_back(goomba2); 
}

void GameManager::startLevel(vector<Entity*>& entities) {

    if (!entities.empty()) {
        for (Entity* ent : entities) {
            delete ent; // free memory of each entity
        }
        entities.clear(); // clean el vector
    }

    buildLevel(entities, 16, 28, 100); //build level will create all the landscape (blocks and other elements of the map)
    createGoomba(entities); //create all the enemies (only goombas for the moment)
}

void GameManager::mapCreated() {

    levelStarted = true;
}

void GameManager::die() {

    levelStarted = false;
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
    if (IsKeyPressed(KEY_DOWN)) {
        opDown();
    }
    else if (IsKeyPressed(KEY_UP)) {
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
        soundPlayedOnce = false;
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

void GameManager::drawScreen(Camera2D c, int width, int heigh) {
    switch (titleScreen) {
    case 0: //in-game screen
        DrawTextureRec(
            backgroundTexture,
            Rectangle{ c.target.x, 0.0f, (float)width, (float)heigh },
            Vector2{ 0.0f, -32.0f },
            WHITE
        );
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
