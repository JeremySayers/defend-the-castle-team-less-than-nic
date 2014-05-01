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
#include <iostream>
#include "GraphicsRenderer.h"
#include <Windows.h>
#include "MenuScreen.h"
#include "GameScreen.h"


using namespace std;

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
bool fullscreen = false;
bool playHover = false;
SDL_Event e;

bool keyEnter = false;

//Keep track of what screen you are on.
//0 = Menu; 1 = Game;
int currentScreen = 0;

unsigned int start;
int FPS = 60;

//Initilizing functions and some helpful ones
void close();
void gameloop();
void eventHandler();
void paint();

std::string exePath();

//Don't use as a pointer for now, everything will work but fullscreen...
GraphicsRenderer ren(SCREEN_HEIGHT, SCREEN_WIDTH);
MenuScreen menuScreen(ren);
GameScreen gameScreen(ren);


int main(int argc, char** argv) {
    //Sets everything up, closes if it fails
    //GraphicsRenderer ren(SCREEN_HEIGHT, SCREEN_WIDTH);
    gameloop();

    close();

    return 0;
}

void gameloop(){
    while (!quit) {
        //Controls how fast the loop goes by grabbing the starting time.
        start = SDL_GetTicks();
        
        eventHandler();
        paint();
        if (currentScreen == 1){
            gameScreen.mainGameLoop();
            if (gameScreen.quitGame) quit = true;
        }
        
        
        //If the last iteration took less than 1/60th of a second delay for an 
        //amount of time to make it so it did.
        if (1000/FPS > SDL_GetTicks() - start)
            SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
    }
}

void eventHandler() {
    while (SDL_PollEvent(&e) != 0) {
        if (currentScreen == 0) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_KEYDOWN) {

                if (e.key.keysym.sym == SDLK_f) {
                    if (!fullscreen) {
                        ren.setFullscreen(true);
                        if (currentScreen == 0)
                            menuScreen.loadMedia();
                        else if (currentScreen == 1)
                            gameScreen.loadMedia();
                        paint();
                        fullscreen = !fullscreen;
                    } else {
                        ren.setFullscreen(false);
                        if (currentScreen == 0)
                            menuScreen.loadMedia();
                        else if (currentScreen == 1)
                            gameScreen.loadMedia();
                        paint();
                        fullscreen = !fullscreen;
                    }
                }

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if ((x > 242 && x < 391) && (y > 269 && y < 344))
                    currentScreen = 1;
            }

            if (e.type == SDL_MOUSEMOTION) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if ((x > 242 && x < 391) && (y > 269 && y < 344)) playHover = true;
                else playHover = false;
            }
        } else if (currentScreen == 1) {
            gameScreen.eventHandling(e);
            /*
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_KEYDOWN) {

                if (e.key.keysym.sym == SDLK_f) {
                    if (!fullscreen) {
                        ren.setFullscreen(true);
                        if (currentScreen == 0)
                            menuScreen.loadMedia();
                        else if (currentScreen == 1)
                            gameScreen.loadMedia();
                        paint();
                        fullscreen = !fullscreen;
                    } else {
                        ren.setFullscreen(false);
                        if (currentScreen == 0)
                            menuScreen.loadMedia();
                        else if (currentScreen == 1)
                            gameScreen.loadMedia();
                        paint();
                        fullscreen = !fullscreen;
                    }
                }

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                
                if (e.key.keysym.sym == SDLK_ENTER){
                    keyEnter = true;
                    gameScreen.grabKeys(keyEnter);
                    keyEnter = false;
                }
            }
            */
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
    if (currentScreen == 0)
        menuScreen.render(playHover);
    else if (currentScreen == 1)
        gameScreen.render();
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