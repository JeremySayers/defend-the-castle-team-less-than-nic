
#include "GraphicsRenderer.h"

/* 
 * File:   MenuScreen.cpp
 * Author: Jeremy Sayers
 * 
 * Created on April 29, 2014, 5:43 PM
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include "GameScreen.h"
#include "EnemyOne.h"
#include "FireDefense.h"
#include <Windows.h>
#include "Castle.h"

using namespace std;

SDL_Texture* GameBackground;
SDL_Texture* HealthBarBG;
SDL_Texture* HealthBarFG;
SDL_Texture* EnemyOneWalk[8];
SDL_Texture* EnemyOneAttack[8];
SDL_Texture* FireGuyDefense[24];
SDL_Texture* MagicGuyDefense[18]
SDL_Texture* Numbers[9];

//Array of enemies.
EnemyOne enemies[10000];
int currentNumEnemies = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Castle Object
Castle player;

FireDefense fireDefense;
int frameGap = 5;
int frame = 0;
int maxFrame = 60;

bool keyEnterStore;
bool displayEnemyOne = false;
bool gameActive = false;
int yOffset; 

int timeSinceLastSpawn = 0;

GraphicsRenderer renGame;

//Game Logic Variables
bool gameStart = false;

void GameScreen::mainGameLoop() {
    if (gameActive) {
        player.calcHealthBarFGWidth();
        timeSinceLastSpawn++;
        if (timeSinceLastSpawn >= 40){
            spawnEnemy();           
            
            timeSinceLastSpawn = 0;
        }
        enemyTick();
    }
}

void GameScreen::enemyTick(){
    if (frame < 60){
        if (frame%frameGap==0){
            for (int i = 0; i < currentNumEnemies; i++){
                if (enemies[i].currentAnimationFrame < 7)
                    enemies[i].incrementAnimationFrame();
                else enemies[i].resetAnimationFrame();
            }
            if (fireDefense.currentAnimationFrame < 23)
                fireDefense.currentAnimationFrame++;
            else fireDefense.currentAnimationFrame = 0;
        }
        frame++;
    } else {
        frame = 0;
        if (frame%frameGap==0){
           for (int i = 0; i < currentNumEnemies; i++){
                if (enemies[i].currentAnimationFrame < 7)
                    enemies[i].incrementAnimationFrame();
                else enemies[i].resetAnimationFrame();
            }
           if (fireDefense.currentAnimationFrame < 23)
                fireDefense.currentAnimationFrame++;
            else fireDefense.currentAnimationFrame = 0;
        }
    }
    for (int i = 0; i < currentNumEnemies; i++){
        if (enemies[i].enemyRect.x < 350){
            enemies[i].enemyRect.x++;
        } else {
            enemies[i].walkAnim = false;
            enemies[i].attackAnim = true;
        }
        if (enemies[i].attackAnim){
            player.health--;
            player.calcHealthBarFGWidth();
        }
    }
}

void GameScreen::castleHealthBar(){
    renGame.renderTexture(HealthBarBG, player.healthBarBG);
    renGame.renderTexture(HealthBarFG, player.healthBarFG);
}

void GameScreen::enemyHealthBars(){
    for (int i = 0; i < currentNumEnemies; i++){
        enemies[i].calcHealthBarFGWidth();
        enemies[i].healthBarBG.x = enemies[i].enemyRect.x+3;
        enemies[i].healthBarBG.y = enemies[i].enemyRect.y-10;
        enemies[i].healthBarFG.x = enemies[i].enemyRect.x+4;
        enemies[i].healthBarFG.y = enemies[i].enemyRect.y-9;
        renGame.renderTexture(HealthBarBG, enemies[i].healthBarBG);
        renGame.renderTexture(HealthBarFG, enemies[i].healthBarFG);
    }
}

void GameScreen::renderFireGuy(){
    renGame.renderTexture(FireGuyDefense[fireDefense.currentAnimationFrame], fireDefense.fireGuyRect);
}

void GameScreen::spawnEnemy(){
    yOffset = rand() % 40 + 1;
    
    enemies[currentNumEnemies].active = true;
    enemies[currentNumEnemies].enemyRect.y+=yOffset;
    currentNumEnemies++;
}

GameScreen::GameScreen(GraphicsRenderer r) {
    GameBackground = NULL;
    renGame = r;
    quitGame = false;
    srand(time(NULL));    

    if (!loadMedia());
}

void GameScreen::render() {
    renGame.renderTexture(GameBackground);
    for (int i = 0; i < currentNumEnemies; i++){
        if (enemies[i].walkAnim){
            renGame.renderTexture(EnemyOneWalk[enemies[i].currentAnimationFrame], enemies[i].enemyRect );
        } else if (enemies[i].attackAnim){
            renGame.renderTexture(EnemyOneAttack[enemies[i].currentAnimationFrame], enemies[i].enemyRect );
        }
    }
    castleHealthBar();
    enemyHealthBars();
    renderFireGuy();
}

bool GameScreen::loadMedia() {
    GameBackground = renGame.loadTexture(exePath() + "\\Images\\GameBackground.png");
    HealthBarBG = renGame.loadTexture(exePath() + "\\Images\\HealthBarBG.png");
    HealthBarFG = renGame.loadTexture(exePath() + "\\Images\\HealthBarFG.png");
    
    //FireGuy Frames
    FireGuyDefense[0] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire1.png");
    FireGuyDefense[1] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire2.png");
    FireGuyDefense[2] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire3.png");
    FireGuyDefense[3] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire4.png");
    FireGuyDefense[4] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire5.png");
    FireGuyDefense[5] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire6.png");
    FireGuyDefense[6] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire7.png");
    FireGuyDefense[7] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire8.png");
    FireGuyDefense[8] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire9.png");
    FireGuyDefense[9] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire10.png");
    FireGuyDefense[10] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire11.png");
    FireGuyDefense[11] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire12.png");
    FireGuyDefense[12] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire13.png");
    FireGuyDefense[13] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire14.png");
    FireGuyDefense[14] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire15.png");
    FireGuyDefense[15] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire16.png");
    FireGuyDefense[16] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire17.png");
    FireGuyDefense[17] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire18.png");
    FireGuyDefense[18] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire19.png");
    FireGuyDefense[19] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire20.png");
    FireGuyDefense[20] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire21.png");
    FireGuyDefense[21] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire22.png");
    FireGuyDefense[22] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire23.png");
    FireGuyDefense[23] = renGame.loadTexture(exePath() + "\\Images\\FireGuy\\Fire24.png");
    
    //Numbers
    Numbers[0] = renGame.loadTexture(exePath() + "\\Images\\Sym\\0.png");
    Numbers[1] = renGame.loadTexture(exePath() + "\\Images\\Sym\\1.png");
    Numbers[2] = renGame.loadTexture(exePath() + "\\Images\\Sym\\2.png");
    Numbers[3] = renGame.loadTexture(exePath() + "\\Images\\Sym\\3.png");
    Numbers[4] = renGame.loadTexture(exePath() + "\\Images\\Sym\\4.png");
    Numbers[5] = renGame.loadTexture(exePath() + "\\Images\\Sym\\5.png");
    Numbers[6] = renGame.loadTexture(exePath() + "\\Images\\Sym\\6.png");
    Numbers[7] = renGame.loadTexture(exePath() + "\\Images\\Sym\\7.png");
    Numbers[8] = renGame.loadTexture(exePath() + "\\Images\\Sym\\8.png");
    Numbers[9] = renGame.loadTexture(exePath() + "\\Images\\Sym\\9.png");
    
    
    //EnemyOneWalk Animations
    EnemyOneWalk[0] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk1.png");
    EnemyOneWalk[1] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk2.png");
    EnemyOneWalk[2] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk3.png");
    EnemyOneWalk[3] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk4.png");
    EnemyOneWalk[4] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk5.png");
    EnemyOneWalk[5] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk6.png");
    EnemyOneWalk[6] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk7.png");
    EnemyOneWalk[7] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAnimations\\Walk8.png");
    
    //EnemyOneAttack Animations
    EnemyOneAttack[0] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack3.png");
    EnemyOneAttack[1] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack2.png");
    EnemyOneAttack[2] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack3.png");
    EnemyOneAttack[3] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack4.png");
    EnemyOneAttack[4] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack5.png");
    EnemyOneAttack[5] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack6.png");
    EnemyOneAttack[6] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack7.png");
    EnemyOneAttack[7] = renGame.loadTexture(exePath() + "\\Images\\EnemyOneAttackAnims\\Attack2.png");

}

void GameScreen::eventHandling(SDL_Event f){
    if (f.type == SDL_KEYDOWN){
        if (f.key.keysym.sym == SDLK_g){
            gameActive = true;
        }
        if (f.key.keysym.sym == SDLK_ESCAPE){
            quitGame = true;
        }
    }
    
    if (f.type == SDL_QUIT){
        quitGame = true;
    }
}

std::string GameScreen::exePath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}
