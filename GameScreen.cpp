/* 
 * File:   MenuScreen.cpp
 * Author: Jeremy Sayers
 * 
 * Created on April 29, 2014, 5:43 PM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "GameScreen.h"
#include "EnemyOne.h"
#include <Windows.h>

using namespace std;

SDL_Texture* GameBackground;
SDL_Texture* EnemyOneWalk[8];

//Array of enemies.
EnemyOne enemies[10];

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool keyEnterStore;
bool displayEnemyOne = false;

GraphicsRenderer renGame;

//Game Logic Variables
bool gameStart = false;

void GameScreen::mainGameLoop() {

}

GameScreen::GameScreen(GraphicsRenderer r) {
    GameBackground = NULL;
    renGame = r;
    quitGame = false;    

    if (!loadMedia());
}

void GameScreen::render() {
    renGame.renderTexture(GameBackground);
    if (displayEnemyOne) renGame.renderTexture(EnemyOneWalk[0], enemies[0].enemyRect );
}

bool GameScreen::loadMedia() {
    GameBackground = renGame.loadTexture(exePath() + "\\Images\\GameBackground.png");
    EnemyOneWalk[0] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk1.png");
    EnemyOneWalk[1] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk2.png");
    EnemyOneWalk[2] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk3.png");
    EnemyOneWalk[3] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk4.png");
    EnemyOneWalk[4] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk5.png");
    EnemyOneWalk[5] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk6.png");
    EnemyOneWalk[6] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk7.png");
    EnemyOneWalk[7] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk8.png");

}

void GameScreen::eventHandling(SDL_Event f){
    if (f.type == SDL_KEYDOWN){
        if (f.key.keysym.sym == SDLK_g){
            displayEnemyOne = true;
        }
        if (f.key.keysym.sym == SDLK_ESCAPE){
            quitGame = true;
        }
    }
    
    if (f.type == SDL_QUIT){
        quitGame = true;
    }
}

std::string GameScreen::exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}
