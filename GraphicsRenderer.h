/* 
 * File:   GraphicsRenderer.h
 * Author: Jeremy
 *
 * Created on March 26, 2014, 9:30 PM
 */

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#ifndef GRAPHICSRENDERER_H
#define	GRAPHICSRENDERER_H

class GraphicsRenderer {
    private:
        bool initSDL();
        bool initRenderer();
        bool initGraphics();
        bool initPNGLoading();
        
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH;
    
    public:
        GraphicsRenderer(int, int);
        
        SDL_Texture* loadTexture(std::string);
        void renderTexture(SDL_Texture*, SDL_Rect);
        void renderTexture(SDL_Texture*);
        void renderClear();
        void renderPresent();
        void setFullscreen(bool);
};

#endif	/* GRAPHICSRENDERER_H */

