/* 
 * File:   InstructionsScreen.cpp
 * Author: Jeremy
 * 
 * Created on May 2, 2014, 3:43 AM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "MenuScreen.h"
#include <Windows.h>
#include "InstructionsScreen.h"

SDL_Texture* BG;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GraphicsRenderer renIn;

InstructionsScreen::InstructionsScreen(GraphicsRenderer r) {
    renIn = r;
    
    if (!loadMedia());
    
}

void InstructionsScreen::render(){
    renIn.renderTexture(BG);
}

bool InstructionsScreen::loadMedia(){
    BG = renIn.loadTexture(exePath() + "\\Images\\Instructions.png");
}

std::string InstructionsScreen::exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}
