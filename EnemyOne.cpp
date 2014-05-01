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
    
    enemyRect.x = 0;  
    enemyRect.y = 360;
    enemyRect.w = 28;
    enemyRect.h = 70;
    currentAnimationFrame = 0;
    
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


