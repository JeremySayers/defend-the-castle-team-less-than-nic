
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
#include <Windows.h>
#include "Castle.h"

using namespace std;

SDL_Texture* GameBackground;
SDL_Texture* HealthBarBG;
SDL_Texture* HealthBarFG;
SDL_Texture* EnemyOneWalk[8];
SDL_Texture* EnemyOneAttack[8];

//Array of enemies.
EnemyOne enemies[10000];
int currentNumEnemies = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Castle Object
Castle player;
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
}

bool GameScreen::loadMedia() {
    GameBackground = renGame.loadTexture(exePath() + "\\Images\\GameBackground.png");
    HealthBarBG = renGame.loadTexture(exePath() + "\\Images\\HealthBarBG.png");
    HealthBarFG = renGame.loadTexture(exePath() + "\\Images\\HealthBarFG.png");
    
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
