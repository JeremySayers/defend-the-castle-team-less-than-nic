
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
#include "MagicGuy.h"

using namespace std;

SDL_Texture* GameBackground;
SDL_Texture* HealthBarBG;
SDL_Texture* HealthBarFG;
SDL_Texture* EnemyOneWalk[8];
SDL_Texture* EnemyOneAttack[8];
SDL_Texture* FireGuyDefense[24];
SDL_Texture* MagicGuyDefense[18];
SDL_Texture* Numbers[10];
SDL_Texture* StatsBG;
SDL_Texture* Plus;
SDL_Texture* Coin;

bool magicPlusHover = false;
bool firePlusHover = false;

SDL_Rect StatsBGRect;
SDL_Rect CoinRect;
//Array of enemies.
EnemyOne enemies[10000];
int currentNumEnemies = 0;
int enemiesKilled = 0;
int enemiesKilledDigits[10];
int enemiesKilledDigitNum = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Magic Cost display
int magicCostDigits[3] = {5,7,3};
int fireCostDigits[3] = {0,0,2};

//Gold the player has
int gold = 200;
int goldDigits[10];
int goldDigitNum = 3;
//Castle Object
Castle player;

FireDefense fireDefense;
MagicGuy magicDefense;
int frameGap = 5;
int spawnGap = 500;
int frame = 0;
int maxFrame = 60;

int healthAdder = 5;

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
        splitGold();
        splitEnemiesKilled();
        if (timeSinceLastSpawn >= spawnGap){
            spawnEnemy();           
            timeSinceLastSpawn = 0;
            if (spawnGap > 50) spawnGap-=30;
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
            if (magicDefense.currentAnimationFrame < 17)
                magicDefense.currentAnimationFrame++;
            else magicDefense.currentAnimationFrame = 0;
        }
        frame++;
    } else {
        //DAMAGE TO ENEMIES DONE HERE BECAUSE IM LAZY AND THIS OCCURS ONCE
        //A SECOND
        damageTick();      
        for (int i = 0; i < currentNumEnemies; i++){
            if (enemies[i].health <= 0 && enemies[i].active){
                enemies[i].active = false;
                enemiesKilled++;
                gold+=20;
            }
        }
        
        frame = 0;
        if (frame%frameGap==0){
           for (int i = 0; i < currentNumEnemies; i++){
                if (enemies[i].currentAnimationFrame < 7)
                    enemies[i].incrementAnimationFrame();
                else enemies[i].resetAnimationFrame();
            }
           if (magicDefense.currentAnimationFrame < 17)
                magicDefense.currentAnimationFrame++;
            else magicDefense.currentAnimationFrame = 0;
        }
    }
    for (int i = 0; i < currentNumEnemies; i++){
        if (enemies[i].active ){
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
}

void GameScreen::castleHealthBar(){
    renGame.renderTexture(HealthBarBG, player.healthBarBG);
    renGame.renderTexture(HealthBarFG, player.healthBarFG);
}

void GameScreen::enemyHealthBars(){
    for (int i = 0; i < currentNumEnemies; i++){
        if (enemies[i].active){
            enemies[i].calcHealthBarFGWidth();
            enemies[i].healthBarBG.x = enemies[i].enemyRect.x+3;
            enemies[i].healthBarBG.y = enemies[i].enemyRect.y-10;
            enemies[i].healthBarFG.x = enemies[i].enemyRect.x+4;
            enemies[i].healthBarFG.y = enemies[i].enemyRect.y-9;
            renGame.renderTexture(HealthBarBG, enemies[i].healthBarBG);
            renGame.renderTexture(HealthBarFG, enemies[i].healthBarFG);
        }
    }
}

void GameScreen::renderFireGuy(){
    renGame.renderTexture(Numbers[fireDefense.amount],fireDefense.amountRect);
    SDL_Rect temp = fireDefense.amountRect;
    temp.x+=20;
    temp.w-=5;
    temp.h-=5;
    renGame.renderTexture(Plus,temp);
    renGame.renderTexture(FireGuyDefense[fireDefense.currentAnimationFrame], fireDefense.fireGuyRect);
}

void GameScreen::renderMagicGuy(){
    renGame.renderTexture(Numbers[magicDefense.amount],magicDefense.amountRect);
    SDL_Rect temp = magicDefense.amountRect;
    temp.x+=20;
    temp.w-=5;
    temp.h-=5; 
    renGame.renderTexture(Plus,temp);
    renGame.renderTexture(MagicGuyDefense[magicDefense.currentAnimationFrame], magicDefense.magicGuyRect);
}

void GameScreen::damageTick(){
    for (int i = 0; i < currentNumEnemies; i++){
        enemies[i].health-=(fireDefense.damage*fireDefense.amount);
        enemies[i].health-=(magicDefense.damage*magicDefense.amount);
    }
}

void GameScreen::spawnEnemy(){
    yOffset = rand() % 40 + 1;
    
    enemies[currentNumEnemies].active = true;
    enemies[currentNumEnemies].enemyRect.y+=yOffset;
    enemies[currentNumEnemies].health+=healthAdder;
    enemies[currentNumEnemies].healthMax+=healthAdder;
    healthAdder+=5;
    currentNumEnemies++;
}

void GameScreen::splitGold(){
    int i = 0;
    int tempGold = gold;
    while (tempGold > 0){
        goldDigits[i] = tempGold%10;
        //cout << goldDigits[i];
        tempGold/=10;
        i++;
    }
    goldDigitNum = i;
    cout << goldDigitNum;
}

void GameScreen::renderGold(){
    SDL_Rect j = CoinRect;
    j.y-=20;
    j.w+=40;
    j.h+=40;
    j.x-=20;
    for (int i = goldDigitNum-1; i >= 0; i--){
        j.x+=25;
        renGame.renderTexture(Numbers[goldDigits[i]],j);
    }
}

void GameScreen::splitEnemiesKilled(){
    int i = 0;
    int tempEnemiesKilled = enemiesKilled;
    while (tempEnemiesKilled > 0){
        enemiesKilledDigits[i] = tempEnemiesKilled%10;
        //cout << goldDigits[i];
        tempEnemiesKilled/=10;
        i++;
    }
    enemiesKilledDigitNum = i;
}

void GameScreen::renderEnemiesKilled(){
    SDL_Rect j = CoinRect;
    j.y-=20;
    j.w+=40;
    j.h+=40;
    j.x+=100;
    for (int i = enemiesKilledDigitNum-1; i >= 0; i--){
        j.x+=25;
        renGame.renderTexture(Numbers[enemiesKilledDigits[i]],j);
    }
}

void GameScreen::renderMagicCost(){
    SDL_Rect temp = magicDefense.amountRect;
    temp.y-=10;
    temp.x-=20;
    temp.w-=5;
    temp.h-=5;
    for (int i = 3-1; i >= 0; i--){
        temp.x+=25;
        renGame.renderTexture(Numbers[magicCostDigits[i]],temp);
    }
}

void GameScreen::renderFireCost(){
    SDL_Rect temp = fireDefense.amountRect;
    temp.y-=10;
    temp.x+=20;
    temp.w-=5;
    temp.h-=5;
    for (int i = 3-1; i >= 0; i--){
        temp.x+=25;
        renGame.renderTexture(Numbers[fireCostDigits[i]],temp);
    }
}

GameScreen::GameScreen(GraphicsRenderer r) {
    GameBackground = NULL;
    renGame = r;
    quitGame = false;
    srand(time(NULL));    

    StatsBGRect.x = 300;
    StatsBGRect.y = 0;
    StatsBGRect.w = 340;
    StatsBGRect.h = 60;
    
    CoinRect.x = 310;
    CoinRect.y = 5;
    CoinRect.w = 16;
    CoinRect.h = 16;
    
    if (!loadMedia());
}

void GameScreen::render() {
    renGame.renderTexture(GameBackground);
    for (int i = 0; i < currentNumEnemies; i++){
        if (enemies[i].active){
            if (enemies[i].walkAnim){
                renGame.renderTexture(EnemyOneWalk[enemies[i].currentAnimationFrame], enemies[i].enemyRect );
            } else if (enemies[i].attackAnim){
                renGame.renderTexture(EnemyOneAttack[enemies[i].currentAnimationFrame], enemies[i].enemyRect );
            }
        }
    }
    castleHealthBar();
    enemyHealthBars();
    renderFireGuy();
    renderMagicGuy();
    renGame.renderTexture(StatsBG,StatsBGRect);
    renGame.renderTexture(Coin,CoinRect);
    renderGold();
    renderEnemiesKilled();
    if (magicPlusHover)renderMagicCost();
    if (firePlusHover)renderFireCost();
}

bool GameScreen::loadMedia() {
    GameBackground = renGame.loadTexture(exePath() + "\\Images\\GameBackground.png");
    HealthBarBG = renGame.loadTexture(exePath() + "\\Images\\HealthBarBG.png");
    HealthBarFG = renGame.loadTexture(exePath() + "\\Images\\HealthBarFG.png");
    
    //Stats Background
    StatsBG = renGame.loadTexture(exePath() + "\\Images\\GrayBlock.png");
    
    //Gold Coin
    Coin = renGame.loadTexture(exePath() + "\\Images\\Coin.png");
    
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
    
    //Magic Guy Defense
    MagicGuyDefense[0] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M1.png");
    MagicGuyDefense[1] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M2.png");
    MagicGuyDefense[2] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M3.png");
    MagicGuyDefense[3] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M4.png");
    MagicGuyDefense[4] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M5.png");
    MagicGuyDefense[5] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M6.png");
    MagicGuyDefense[6] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M7.png");
    MagicGuyDefense[7] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M8.png");
    MagicGuyDefense[8] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M9.png");
    MagicGuyDefense[9] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M10.png");
    MagicGuyDefense[10] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M11.png");
    MagicGuyDefense[11] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M12.png");
    MagicGuyDefense[12] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M13.png");
    MagicGuyDefense[13] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M14.png");
    MagicGuyDefense[14] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M15.png");
    MagicGuyDefense[15] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M16.png");
    MagicGuyDefense[16] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M17.png");
    MagicGuyDefense[17] = renGame.loadTexture(exePath() + "\\Images\\MagicGuy\\M18.png");
    
    
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
    
    Plus = renGame.loadTexture(exePath() + "\\Images\\Sym\\plus.png");
    
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
    
    if (f.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_Rect temp = magicDefense.amountRect;
        temp.x+=20;
        temp.w-=5;
        temp.h-=5;
        SDL_GetMouseState(&x, &y);
        if ((x > temp.x && x < temp.x+temp.w) && (y > temp.y && y < temp.y+temp.h)){
            magicPlusHover = true;
            cout << "ITS TRYE";
        } else {
            magicPlusHover = false;
            cout << "NOPEPEPE";
        }
        SDL_Rect temp2 = fireDefense.amountRect;
        temp2.x+=20;
        temp2.w-=5;
        temp2.h-=5;
        if ((x > temp2.x && x < temp2.x+temp2.w) && (y > temp2.y && y < temp2.y+temp2.h)){
            firePlusHover = true;
            cout << "ITS TRYE";
        } else {
            firePlusHover = false;
            cout << "NOPEPEPE";
        }
     }
    
    if (f.type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_Rect temp = magicDefense.amountRect;
        temp.x+=20;
        temp.w-=5;
        temp.h-=5;
        SDL_GetMouseState(&x, &y);
        if ((x > temp.x && x < temp.x+temp.w) && (y > temp.y && y < temp.y+temp.h)){
            if (gold >=magicDefense.cost){
                magicDefense.amount++;
                gold-=magicDefense.cost;
            }
        }
        SDL_Rect temp2 = fireDefense.amountRect;
        temp2.x+=20;
        temp2.w-=5;
        temp2.h-=5;
        if ((x > temp2.x && x < temp2.x+temp2.w) && (y > temp2.y && y < temp2.y+temp2.h)){
            if (gold >=fireDefense.cost){
                fireDefense.amount++;
                gold-=fireDefense.cost;
            }
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
