/* 
 * File:   Castle.cpp
 * Author: Jeremy
 * 
 * Created on May 1, 2014, 8:23 PM
 */

#include "Castle.h"

Castle::Castle() {
    healthMax = 3000;
    health = 3000;
    healthBarBG.x = 380;
    healthBarBG.y = 220;
    healthBarBG.w = 150;
    healthBarBG.h = 14;
    
    healthBarFG.x = 382;
    healthBarFG.y = 222;
    healthBarFG.w = 146;
    healthBarFG.h = 10;
}

void Castle::calcHealthBarFGWidth(){
    healthBarFG.w = ((healthBarBG.w * health) / healthMax)-1;
}

