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

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
bool fullscreen = false;
bool playHover = false;
SDL_Event e;

//Initilizing functions and some helpful ones
bool initSDL();
bool initRenderer();
bool initGraphics();
bool loadMedia();
bool initPNGLoading();
void close();
void gameloop();
void eventHandler();
void paint();

GraphicsRenderer* ren;

//Some texture objects
SDL_Texture* MainMenuTexture = NULL;
SDL_Texture* PlayRest = NULL;
SDL_Texture* PlayHover = NULL;

//A rect object to hold the position of the button
SDL_Rect PlayRect;

int main(int argc, char** argv) {
    //Sets everything up, closes if it fails
    GraphicsRenderer ren(SCREEN_HEIGHT, SCREEN_WIDTH);
    loadMedia();
    gameloop();

    close();

    return 0;
}

bool loadMedia(){
    MainMenuTexture = ren->loadTexture("C:/Users/Jeremy/Documents/NetBeansProjects/Defend the Castle/dist/Debug/MinGW-Windows/Images/Background.png");
    
    PlayRect.x = (SCREEN_WIDTH/2)-75;
    PlayRect.y = (SCREEN_HEIGHT/2) + 50;
    PlayRect.w = 150;
    PlayRect.h = 60;
    PlayRest = ren->loadTexture("C:/Users/Jeremy/Documents/NetBeansProjects/Defend the Castle/dist/Debug/MinGW-Windows/Images/PlayRest.png");
    PlayHover = ren->loadTexture("C:/Users/Jeremy/Documents/NetBeansProjects/Defend the Castle/dist/Debug/MinGW-Windows/Images/PlayHover.png");
    if (MainMenuTexture == NULL){
        printf("Dat image, ya nope not here: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
    
}

void gameloop(){
    while (!quit) {
        eventHandler();
        paint();
    }
}

void eventHandler(){
    while (SDL_PollEvent(&e) != 0) {
        
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_f) {
                if (!fullscreen) {
                    ren->setFullscreen(true);
                    loadMedia();
                    paint();
                    fullscreen = !fullscreen;
                } else {
                    ren->setFullscreen(false);
                    loadMedia();
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

void renderPlayButton(){
    if (playHover) ren->renderTexture(PlayHover, PlayRect);
    else ren->renderTexture(PlayRest, PlayRect);
}

void paint(){
    ren->renderClear();
    ren->renderTexture(MainMenuTexture);
    renderPlayButton();
    ren->renderPresent();
}

void close(){
    //SDL_DestroyRenderer(GameRenderer);
    //SDL_DestroyWindow(GameWindow);
    SDL_DestroyTexture(MainMenuTexture);
    SDL_Quit();
}