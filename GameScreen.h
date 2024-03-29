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
        void splitGold();
        void renderGold();
        void splitEnemiesKilled();
        void renderEnemiesKilled();
        void renderMagicCost();
        void renderFireCost();
        void damageTick();
        void gameOver();
        void renderGameOver();

};

#endif	/* GAMESCREEN_H */

