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
SDL_Texture* Title;
SDL_Rect PlayRect2;
SDL_Rect TitleRect;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GraphicsRenderer renMenu;

MenuScreen::MenuScreen(GraphicsRenderer r) {
    MainMenuTexture2 = NULL;
    PlayRest2 = NULL;
    PlayHover2 = NULL;
    Title = NULL;
    
    renMenu = r;

    SDL_Rect PlayRect2;
    
    if (!loadMedia());
}

void MenuScreen::render(bool playHover){
    renMenu.renderTexture(MainMenuTexture2);
    renMenu.renderTexture(Title, TitleRect);
    if (playHover)
        renMenu.renderTexture(PlayHover2, PlayRect2);
    else
        renMenu.renderTexture(PlayRest2, PlayRect2);
}

bool MenuScreen::loadMedia(){
    MainMenuTexture2 = renMenu.loadTexture(exePath() + "\\Images\\Background.png");
    Title = renMenu.loadTexture(exePath() + "\\Images\\Title.png");
            
    TitleRect.x = (SCREEN_WIDTH/2)-200;  
    TitleRect.y = 100;
    TitleRect.w = 400;
    TitleRect.h = 100;
    
    PlayRect2.x = (SCREEN_WIDTH/2)-75;
    PlayRect2.y = (SCREEN_HEIGHT/2) + 50;
    PlayRect2.w = 150;
    PlayRect2.h = 60;
    
    PlayRest2 = renMenu.loadTexture(exePath() + "\\Images\\Play Black.png");
    PlayHover2 = renMenu.loadTexture(exePath() + "\\Images\\Play Yellow.png");
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
