#include "GameManager.hpp"


GameManager::GameManager(int screen, int op_, Player* player_)
    : titleScreen(screen), op(op_), player(player_) {

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
    invincibility = LoadSound("resources/audio/InvincibilityTheme.wav");
    meMario = LoadSound("resources/audio/meMario.wav");
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
    UnloadSound(invincibility);
    UnloadSound(meMario);
#pragma endregion
}

vector<Entity*> GameManager::allEntities;

void GameManager::update() {

    if (titleScreen == 2) { opSelector(); } //for choosing an option in the main menu
    nextScreen();

}
void GameManager::buildPowerUps(const string& filename, int rows, int columns) {

    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de mapa: " << filename << std::endl;
        return;
    }
    else {

        printf("fileOpnenedPowerUps\n");
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            file >> mapPowerUps[row][col];
        }
    }

    file.close();
}

void GameManager::manageEntities(float gravity) {

    for (auto it = allEntities.begin(); it != allEntities.end(); ) {
        Entity* entity = *it;
        entity->update(allEntities, gravity);

        if (entity->getToDelate()) {

            printf("entity id: %d DELETED", entity->getId());
            delete entity;
            it = allEntities.erase(it);
        }
        else {
            ++it;
        }
    }
}

void GameManager::buildLevel(int tileSize_, int rows_, int col_) {
    const int TILE_SIZE = tileSize_;
    int row = rows_;
    int col = col_;

    LoadMapFromFile("resources/assets/map.txt", rows_, col_);
    buildPowerUps("resources/assets/powerUpsPosition.txt", rows_, col_);

    //traverse all the array
    for (int row = 0; row < 28; ++row) {
        for (int col = 0; col < 224; ++col) {
            int tile = map[row][col];
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;

            //for each tile place the correct block
            switch (tile) {
            case 1: //invisibleBlocks
                allEntities.push_back(new NormalBlock(x, y, TILE_SIZE, TILE_SIZE, 2, 1, 1));
                break;
            case 2: { //surpriseBlock

                SurpriseBlock* s = new SurpriseBlock(x, y, TILE_SIZE, TILE_SIZE, 2, 1, 2);

                int tilePower = mapPowerUps[row][col];

                switch (tilePower) {

                case 1: {//mushroom
                    Mushroom* mushroom = new Mushroom(x, y, TILE_SIZE, TILE_SIZE, 3, 1, 1);

                    allEntities.push_back(mushroom);//add the mushroom to the entity list
                    s->getPowerUp(mushroom);//asigns to that spececific surpirse block an stored powerUp
                }
                    break;

                case 2: {//flower

                    Flower* flower = new Flower(x, y, TILE_SIZE, TILE_SIZE, 3, 1, 2);

                    allEntities.push_back(flower);//add the flower to the entity list
                    s->getPowerUp(flower);//asigns to that spececific surpirse block an stored powerUp
                }
                    break;

                case 3: {//star
                    Star* star = new Star(x, y, TILE_SIZE, TILE_SIZE, 3, 1, 3);

                    allEntities.push_back(star);//add the star to the entity list
                    s->getPowerUp(star); //asigns to that spececific surpirse block an stored powerUp

                }
                    break;

                case 4:{ //coin
                    Coin* coin = new Coin(x, y, TILE_SIZE, TILE_SIZE, 3, 1, 4, true, player);

                    allEntities.push_back(coin);//add the coin to the entity list
                    s->getPowerUp(coin);//asigns to that spececific surpirse block an stored powerUp
                    
                    }
                      break;

                default:
                    break;
                }

                allEntities.push_back(s);//add suprise block

                break;
            }
             
            case 3: { //breakBlock

                allEntities.push_back(new BreakBlock(x, y, TILE_SIZE, TILE_SIZE, 2, 1, 3, false, 0.0f, 0));
                break;
            }
            case 4: { //pipe

                createPiranha(x, y); //create piranha when finding a pipe
                allEntities.push_back(new Pipe(x, y, 32, 64, 2, 1));

                //allEntities.push_back(new NormalBlock(x, y, pipe.width, pipe.height, 2, 1, 1)); //create the invisible blocks for the pipe
                break;
            }
            case 5: { //coins that are not inside blocks
                allEntities.push_back(new Coin(x, y, TILE_SIZE, TILE_SIZE, 3, 1, 4, false, player));//add the coin to the entity list

                break;
            }
            case 6: { //flag
                allEntities.push_back(new Entity(x, y, 16, 144, 5, 1)); //pole
                allEntities.push_back(new Flag(x - 8, y, 16, 16, 6, 1)); //flag

                break;
            }
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
    else {
        printf("fileMapOpened\n");
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            file >> map[row][col];
        }
    }

    file.close();
}


void GameManager::createGoomba() {

    printf("goombas created\n");

    Goomba* goomba = new Goomba(400.0f, 300.0f, 16, 16, 1, 1, 'g', 100.0f, 1);
    allEntities.push_back(goomba);

    Goomba* goomba2 = new Goomba(500.0f, 300.0f, 16, 16, 1, 1, 'g', 100.0f, -1);
    allEntities.push_back(goomba2); 

    Goomba* goomba3 = new Goomba(770.0f, 300.0f, 16, 16, 1, 1, 'g', 100.0f, -1);
    allEntities.push_back(goomba3);

    Goomba* goomba4 = new Goomba(2730.0f, 300.0f, 16, 16, 1, 1, 'g', 100.0f, -1);
    allEntities.push_back(goomba4);
}

void GameManager::createPiranha(float x, float y) {
    allEntities.push_back(new Piranha(x + 8.0f, y + 16.0f, 16, 23, 1, 1, 'p'));
}


void GameManager::startLevel() {

    if (!allEntities.empty()) {
        for (Entity* ent : allEntities) {
            delete ent; // free memory of each entity
        }
        allEntities.clear(); // clean el vector
    }

    buildLevel(16, 28, 224); //build level will create all the landscape (blocks and other elements of the map)
    createGoomba(); //create all the enemies (only goombas for the moment)
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
    if (titleScreen == 1 || titleScreen == 3 || titleScreen == 4 || titleScreen == 5) {
        float clock = counterBack(3.0f);
        if (clock <= 0) {

            //if the screen is the credits, win or lose screen, go to main menu screen
            if (titleScreen == 1 || titleScreen == 4 || titleScreen == 5) { 
                soundPlayedOnce = false;
                titleScreen = 2; 
            }
            if (titleScreen == 3) { titleScreen = 0; }//go to game screen

        }
    }

    if (IsKeyPressed(KEY_N)) {
        if (titleScreen == 2) { //if in the main menu
            if (op == 0) { titleScreen = 3; } //go to startGame screen
            else if (op == 1) {  titleScreen = 6; } //go to howToPlay 1
            else if (op == 2) { CloseWindow(); } //close game
        }
        else if (titleScreen == 6) { titleScreen = 7; } //go to how to play 2
        else if (titleScreen == 7) { titleScreen = 2; } //go to main menu
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
        if (player->getHasPowerUp() == 2) {

            printf("plating invencibility\n");

            if (!IsSoundPlaying(invincibility)) {
                PlaySound(invincibility);
                StopSound(levelS);
            }
        }
        else {

            if (!IsSoundPlaying(levelS)) {
                PlaySound(levelS);
                StopSound(invincibility);
            }
        }
        break;

    case 1: //title screen
        PlaySound(meMario);
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
            Vector2{ 0.0f, 0.0f },
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


float GameManager::counterBack(float initialTime) {

    if (startCounterTime < 0.0f) {
        startCounterTime = GetTime(); // guarda el tiempo inicial solo una vez
    }

    float elapsed = GetTime() - startCounterTime;
    float remaining = initialTime - elapsed;

    if (remaining <= 0.0f) {
        startCounterTime = -1.0f; // reinicia para una futura llamada
        return 0.0f;
    }

    return remaining;
}


