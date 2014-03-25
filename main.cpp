/* 
 * File:   main.cpp
 * Author: Jeremy
 *
 * Created on March 24, 2014, 11:00 PM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

//GLOBAL VARIABLES
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
bool fullscreen = false;

bool initSDL();
bool initRenderer();
bool initGraphics();
bool loadMedia();
void pngLoading();
void close();
void gameloop();
void eventHandler();
void paint();

SDL_Texture* loadTexture(std::string);

SDL_Window* GameWindow = NULL;
SDL_Texture* MainMenuTexture = NULL;
SDL_Renderer* GameRenderer = NULL;
SDL_Event e;

int main(int argc, char** argv) {
    if (!initSDL()) close();
    if (!initGraphics()) close();
    if (!initRenderer()) close();
    if (!loadMedia()) close;
    pngLoading();
    
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

bool initRenderer(){
    GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if (GameRenderer == NULL){
        printf("YOU DONE GOOFED RENDERER %s\n", SDL_GetError());
        return false;
    } else {
        SDL_SetRenderDrawColor(GameRenderer, 0xBB, 0xF4, 0xCC, 0xFF);
        return true;
    }
}

bool initGraphics() {
    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (GameWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

void pngLoading(){
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("Nope");
    }
}

SDL_Texture* loadTexture(std::string path){
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL){
        printf("I couldnt load that for god knows why %s\n", IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(GameRenderer, loadedSurface);
        if (newTexture == NULL){
            printf("Again with this shit? %s\n", IMG_GetError());
        }
        
        SDL_FreeSurface(loadedSurface);
    }
    
    return newTexture;
}
bool loadMedia(){
    MainMenuTexture = loadTexture("C:\\Users\\Jeremy\\Documents\\NetBeansProjects\\Defend the Castle\\dist\\Debug\\MinGW-Windows\\Images\\MainMenuImage.png");
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
                    SDL_DestroyRenderer(GameRenderer);
                    GameRenderer = NULL;
                    SDL_DestroyWindow(GameWindow);
                    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
                    GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
                    loadMedia();
                    paint();
                    fullscreen = !fullscreen;
                } else {
                    SDL_DestroyRenderer(GameRenderer);
                    GameRenderer = NULL;
                    SDL_DestroyWindow(GameWindow);
                    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
                    GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
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
    }
}

void paint(){
    SDL_RenderClear(GameRenderer);
    SDL_RenderCopy(GameRenderer, MainMenuTexture, NULL, NULL);
    SDL_RenderPresent(GameRenderer);
}

void close(){
    SDL_DestroyWindow(GameWindow);
    SDL_DestroyTexture(MainMenuTexture);
    SDL_Quit();
}

