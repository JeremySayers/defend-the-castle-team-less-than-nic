#include <string>
#include "GraphicsRenderer.h"
#include <stdio.h>
using namespace std;

SDL_Window* GameWindow;
SDL_Window* GameWindowTest;
SDL_Renderer* GameRenderer;
int SCREEN_HEIGHT;
int SCREEN_WIDTH;

GraphicsRenderer::GraphicsRenderer(int h, int w){
    GameWindow = NULL;
    GameRenderer = NULL;
    SCREEN_HEIGHT = h;
    SCREEN_WIDTH = w;
    if (!initSDL());
    if (!initGraphics());
    if (!initRenderer());
    if (!initPNGLoading());
}

GraphicsRenderer::GraphicsRenderer(){
    
}


bool GraphicsRenderer::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL COULDNT LOAD FOO:%s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

bool GraphicsRenderer::initRenderer(){
    GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
    if (GameRenderer == NULL){
        printf("YOU DONE GOOFED RENDERER %s\n", SDL_GetError());
        return false;
    } else {
        SDL_SetRenderDrawColor(GameRenderer, 0xBB, 0xF4, 0xCC, 0xFF);
        return true;
    }
}

bool GraphicsRenderer::initGraphics() {
    GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //GameWindowTest = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (GameWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } else {
        return true;
    }
}

bool GraphicsRenderer::initPNGLoading(){
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        printf("Nope");
        return false;
    } else {
        return true;
    }
}

void GraphicsRenderer::setFullscreen(bool full){
    if (full){
        SDL_DestroyRenderer(GameRenderer);
        GameRenderer = NULL;
        SDL_DestroyWindow(GameWindow);
        GameWindow = NULL;
        GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
        if (GameWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
    } else {
        SDL_DestroyRenderer(GameRenderer);
        GameRenderer = NULL;
        SDL_DestroyWindow(GameWindow);
        GameWindow = SDL_CreateWindow("Defend the Castle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
    }
}

SDL_Texture* GraphicsRenderer::loadTexture(std::string path){
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

void GraphicsRenderer::renderTexture(SDL_Texture* tex, SDL_Rect rec){
    SDL_RenderCopy(GameRenderer, tex, NULL, &rec);
}

void GraphicsRenderer::renderTexture(SDL_Texture* tex){
    SDL_RenderCopy(GameRenderer, tex, NULL, NULL);
}

void GraphicsRenderer::renderClear(){
    SDL_RenderClear(GameRenderer);
}
void GraphicsRenderer::renderPresent(){
    SDL_RenderPresent(GameRenderer);
}