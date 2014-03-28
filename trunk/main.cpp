/* 
 * File:   main.cpp
 * Author: Jeremy Sayers
 *
 * Created on March 24, 2014, 11:00 PM
 */
 
//Includes 
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "GraphicsRenderer.h"
#include <Windows.h>
#include "MenuScreen.h"

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
bool fullscreen = false;
bool playHover = false;
SDL_Event e;

//Initilizing functions and some helpful ones
void close();
void gameloop();
void eventHandler();
void paint();

std::string exePath();

//Don't use as a pointer for now, everything will work but fullscreen...
GraphicsRenderer ren(SCREEN_HEIGHT, SCREEN_WIDTH);
MenuScreen menuScreen(ren);


int main(int argc, char** argv) {
    //Sets everything up, closes if it fails
    //GraphicsRenderer ren(SCREEN_HEIGHT, SCREEN_WIDTH);
    gameloop();

    close();

    return 0;
}

void gameloop(){
    while (!quit) {
        eventHandler();
        paint();
    }
}

void eventHandler(){
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) quit = true;
        
        if (e.type == SDL_KEYDOWN) {
 
            if (e.key.keysym.sym == SDLK_f) {
                if (!fullscreen) {
                    ren.setFullscreen(true);
                    menuScreen.loadMedia();
                    paint();
                    fullscreen = !fullscreen;
                } else {
                    ren.setFullscreen(false);
                    menuScreen.loadMedia();
                    paint();
                    fullscreen = !fullscreen;
                }
            }

            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
        
        if (e.type == SDL_MOUSEBUTTONUP){
            int x,y;
            SDL_GetMouseState(&x, &y);
            if ((x > 242 && x < 391) && (y > 269 && y < 344)) quit = true;
        }
        
        if (e.type == SDL_MOUSEMOTION){
            int x,y;
            SDL_GetMouseState(&x, &y);
            if ((x > 242 && x < 391) && (y > 269 && y < 344)) playHover = true;
            else playHover = false;
        }
    }
}
/*
void renderPlayButton(){
    if (playHover) ren.renderTexture(PlayHover, PlayRect);
    else ren.renderTexture(PlayRest, PlayRect);
}
*/

void paint(){
    ren.renderClear();
    menuScreen.render();
    //renderPlayButton();
    ren.renderPresent();
}

void close(){
    //SDL_DestroyRenderer(GameRenderer);
    //SDL_DestroyWindow(GameWindow);
    //SDL_DestroyTexture(MainMenuTexture);
    SDL_Quit();
}

//Gets the current working directory without a trailing slash
std::string exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}