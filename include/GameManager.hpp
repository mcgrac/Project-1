#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "raylib.h"

class GameManager {
private:
    int titleScreen;
    int op;
    bool mapDrawed;

    Texture2D backgroundTexture;
    Texture2D Title_screenTexture;
    Texture2D Game_overTexture;
    Texture2D StrtTexture;
    Texture2D Initial_screenTexture;
    Texture2D howToPlayTexture1;
    Texture2D howToPlayTexture2;
    Texture2D winTexture;

    Texture2D arrowTexture;

public:
    GameManager(int screen, int op_, bool drawed_);
    ~GameManager();

    void mapCreated();
    bool getMapCreated();

    int GetScreen();
    int getOp();
    void setScreen(int titleScreen);

    void drawArrow();
    void opUp();
    void opDown();
    void opSelector();
    void nextScreen();
    void gameOver();
    void drawScreen();
};

#endif
