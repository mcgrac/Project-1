#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "raylib.h"
#include<vector>
#include "Entity.hpp"         
#include "Goomba.hpp"         
#include "Block.hpp"          
#include "SurpriseBlock.hpp"
#include "BreakBlock.hpp"
#include"NormalBlock.hpp"
#include"Star.hpp" //problema
#include"Flower.hpp"//problema
#include"Mushroom.hpp"//problema
#include"Coin.hpp"//problema
#include"BaseObject.hpp" //inlcuded now
#include"Player.hpp"
#include"Piranha.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class GameManager {
private:

    int map[28][224]; //array of numbers of the map (loaded in game)
    /* 0-> no collision
    1->floorBlock
    2->breakBlock
    3->surpriseBlock
    4->finalStaires 
    5->coinsInMap
    6->pole
    7->flag*/

    int mapPowerUps[28][224];
    /* 1->mushroom
       2->flower
       3->star*/

    int titleScreen; //in which screen we are

    //screen 0 -> game
    //screen 1 -> initial screen (credits)
    //screen 2 -> main menu
    //screen 3 -> start level screen
    //screen 4 -> loose screen
    //screen 5 -> win screen
    //screen 6 -> how to play 1
    //screen 7 -> how to play 2

    int op; //arrow selection main menu
    bool soundPlayedOnce = false; //for playing just once some sounds (ex: game over/win sounds)
    bool levelStarted = false; //for restarting the level

    //create a vector that will contain all the entities
    static vector<Entity*> allEntities;

#pragma region TEXTURES
    Texture2D backgroundTexture;
    Texture2D Title_screenTexture;
    Texture2D Game_overTexture;
    Texture2D StrtTexture;
    Texture2D Initial_screenTexture;
    Texture2D howToPlayTexture1;
    Texture2D howToPlayTexture2;
    Texture2D winTexture;
    Texture2D looseTexture;
    Texture2D arrowTexture;

    //pipe
    Texture2D pipe;
#pragma endregion

#pragma region SOUNDS
    Sound levelS;
    Sound gameOverS;
    Sound winS;
#pragma endregion

    Player* player;


public:
    GameManager(int screen, int op_, Player* player_);
    ~GameManager();

    void mapCreated();
    void die();
    void LoadMapFromFile(const string& filename, int rows, int columns);

    void manageEntities(float gravity);

    void buildLevel(int tileSize_, int rows_, int col_);
    void startLevel();
    void buildPowerUps(const string& filename, int rows, int columns);

    int GetScreen();
    int getOp();


    void setScreen(int titleScreen);
    void win();
    void drawArrow();
    void opUp();
    void opDown();
    void opSelector();
    void nextScreen();
    void gameOver();
    void drawScreen(Camera2D c, int width, int heigh);
    void playSounds();

    void createGoomba();
    void createPiranha(float x, float y);

#pragma region GETTERS
    bool getlevelStarted() { return levelStarted; }
    bool retSound() { return soundPlayedOnce; }
    static vector<Entity*>& getAllEntities() {
        return allEntities;
    }
#pragma endregion
};
#endif
