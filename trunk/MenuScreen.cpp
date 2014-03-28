/* 
 * File:   MenuScreen.cpp
 * Author: jsayers
 * 
 * Created on March 28, 2014, 2:10 PM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "MenuScreen.h"
#include <Windows.h>

SDL_Texture* MainMenuTexture2;
SDL_Texture* PlayRest2;
SDL_Texture* PlayHover2;
SDL_Rect PlayRect2;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GraphicsRenderer renMenu;

MenuScreen::MenuScreen(GraphicsRenderer r) {
    MainMenuTexture2 = NULL;
    PlayRest2 = NULL;
    PlayHover2 = NULL;
    
    renMenu = r;

    SDL_Rect PlayRect2;
    
    if (!loadMedia());
}

void MenuScreen::render(){
    renMenu.renderTexture(MainMenuTexture2);
}

bool MenuScreen::loadMedia(){
    MainMenuTexture2 = renMenu.loadTexture(exePath() + "\\Images\\Background.png");
    
    PlayRect2.x = (SCREEN_WIDTH/2)-75;
    PlayRect2.y = (SCREEN_HEIGHT/2) + 50;
    PlayRect2.w = 150;
    PlayRect2.h = 60;
    PlayRest2 = renMenu.loadTexture(exePath() + "\\Images\\PlayRest.png");
    PlayHover2 = renMenu.loadTexture(exePath() + "\\Images\\PlayHover.png");
    if (MainMenuTexture2 == NULL){
        printf("Dat image, ya nope not here: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

std::string MenuScreen::exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}
