/* 
 * File:   MenuScreen.cpp
 * Author: Jeremy Sayers
 * 
 * Created on April 29, 2014, 5:43 PM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "GameScreen.h"
#include <Windows.h>

SDL_Texture* GameBackground;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GraphicsRenderer renGame;

GameScreen::GameScreen(GraphicsRenderer r) {
    GameBackground = NULL;
    renGame = r;

    if (!loadMedia());
}

void GameScreen::render(){
    renGame.renderTexture(GameBackground);
}

bool GameScreen::loadMedia(){
    GameBackground = renGame.loadTexture(exePath() + "\\Images\\GameBackground.png");
}

std::string GameScreen::exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}
