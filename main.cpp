/* 
 * File:   main.cpp
 * Author: Jeremy
 *
 * Created on March 24, 2014, 11:00 PM
 */
#include <SDL.h>
#include <stdio.h>

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
bool fullscreen = false;

bool initSDL();
bool initGraphics();
bool loadMedia();
void close();
void gameloop();
void eventHandler();
void paint();

SDL_Window* GameWindow = NULL;
SDL_Surface* GameSurface = NULL;
SDL_Surface* MainMenuImage = NULL;
SDL_Event e;

int main(int argc, char** argv) {
    if (!initSDL()) close();
    if (!initGraphics()) close();
    if (!loadMedia()) SDL_Delay(3000);

    gameloop();

    close();

    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL COULDNT LOAD FOO:%s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

bool initGraphics() {
    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (GameWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        GameSurface = SDL_GetWindowSurface(GameWindow);
        return true;
    }
}

bool loadMedia(){
    MainMenuImage = SDL_LoadBMP("C:\\Users\\Jeremy\\Documents\\NetBeansProjects\\Defend the Castle\\dist\\Debug\\MinGW-Windows\\Images\\MainMenuImage.bmp");
    if (MainMenuImage == NULL){
        printf("Dat image, ya nope not here: %s\n", SDL_GetError());
        return false;
    } else {
        SDL_BlitSurface(MainMenuImage, NULL, GameSurface, NULL);
        SDL_UpdateWindowSurface(GameWindow);
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
                    SDL_DestroyWindow(GameWindow);
                    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
                    GameSurface = SDL_GetWindowSurface(GameWindow);
                    fullscreen = !fullscreen;
                } else {
                    SDL_DestroyWindow(GameWindow);
                    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                    GameSurface = SDL_GetWindowSurface(GameWindow);
                    fullscreen = !fullscreen;
                }
            }

            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
    }
}

void paint(){
    SDL_BlitSurface(MainMenuImage, NULL, GameSurface, NULL);
    SDL_UpdateWindowSurface(GameWindow);
}

void close(){
    SDL_DestroyWindow(GameWindow);
    SDL_FreeSurface(MainMenuImage);
    SDL_Quit();
}

