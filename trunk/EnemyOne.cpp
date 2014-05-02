/* 
 * File:   EnemyOne.cpp
 * Author: Jeremy
 * 
 * Created on April 29, 2014, 6:43 PM
 */

#include "EnemyOne.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

EnemyOne::EnemyOne() {
    srand(time(NULL));
    
    int yOffset = rand() % 40 + 1;
    
    healthMax = 100;
    health = 100;
    
    enemyRect.x = -40;  
    enemyRect.y = 360;
    enemyRect.w = 28;
    enemyRect.h = 70;
    currentAnimationFrame = 0;
    
    healthBarBG.x = enemyRect.x+2;
    healthBarBG.y = enemyRect.y-10;
    healthBarBG.w = 20;
    healthBarBG.h = 6;
    
    healthBarFG.x = enemyRect.x+3;
    healthBarFG.y = enemyRect.y-9;
    healthBarFG.w = 18;
    healthBarFG.h = 4;
    
    active = false;
    
    walkAnim = true;
    attackAnim = false;
}

void EnemyOne::incrementAnimationFrame(){
    currentAnimationFrame++;
}

void EnemyOne::resetAnimationFrame(){
    currentAnimationFrame = 0;
}

void EnemyOne::calcHealthBarFGWidth(){
    healthBarFG.w = ((healthBarBG.w * health) / healthMax) - 2;
}


