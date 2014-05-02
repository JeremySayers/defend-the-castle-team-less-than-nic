/* 
 * File:   MagicGuy.cpp
 * Author: Jeremy
 * 
 * Created on May 1, 2014, 10:43 PM
 */

#include "MagicGuy.h"

MagicGuy::MagicGuy() {
    amount = 1;
    currentAnimationFrame = 0;
    
    damage = 20;
    cost = 375;
    
    magicGuyRect.x = 225;  
    magicGuyRect.y = 195;
    magicGuyRect.w = 160;
    magicGuyRect.h = 100;
    
    amountRect.x = 355;  
    amountRect.y = 180;
    amountRect.w = 40;
    amountRect.h = 40;
}

