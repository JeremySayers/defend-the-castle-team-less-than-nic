/* 
 * File:   GameScreen.h
 * Author: Jeremy
 *
 * Created on April 29, 2014, 5:44 PM
 */
#include "GraphicsRenderer.h"
#include <string>
#include <stdio.h>

#ifndef GAMESCREEN_H
#define	GAMESCREEN_H

class GameScreen {
    public:
        GameScreen(GraphicsRenderer);
        void render();
        bool loadMedia();
        void mainGameLoop();
        void eventHandling(SDL_Event e);
        void castleHealthBar();
        void enemyHealthBars();
        
        bool quitGame;
    private:
        std::string exePath();
        void enemyTick();
        void spawnEnemy();
        void renderFireGuy();
        void renderMagicGuy();

};

#endif	/* GAMESCREEN_H */

