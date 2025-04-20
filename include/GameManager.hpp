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
#include <iostream>
#include <fstream>

using namespace std;

class GameManager {
private:

    int map[28][100];

    int titleScreen;
    int op;
    bool mapDrawed;
    bool soundPlayedOnce = false;
    bool levelStarted = false;

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

    //sounds
    Sound levelS;
    Sound gameOverS;
    Sound winS;

public:
    GameManager(int screen, int op_, bool drawed_);
    ~GameManager();

    void mapCreated();
    void die();
    bool getMapCreated();
    void LoadMapFromFile(const string& filename, int rows, int columns);

    void buildLevel(vector<Entity*>& entities, int tileSize_, int rows_, int col_);
    void startLevel(vector<Entity*>& entities);

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

    void createGoomba(vector<Entity*>& entities);

    bool getlevelStarted() { return levelStarted; }
    bool retSound() { return soundPlayedOnce; }
};
#endif
