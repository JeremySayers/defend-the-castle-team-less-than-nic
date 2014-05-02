/* 
 * File:   FireDefense.cpp
 * Author: Jeremy
 * 
 * Created on May 1, 2014, 9:46 PM
 */

#include "FireDefense.h"

FireDefense::FireDefense() {
    amount = 0;
    currentAnimationFrame = 0;
    
    damage = 10;
    cost = 200;
    
    fireGuyRect.x = 358;  
    fireGuyRect.y = 260;
    fireGuyRect.w = 100;
    fireGuyRect.h = 100;
    amountRect.x = 430;  
    amountRect.y = 270;
    amountRect.w = 40;
    amountRect.h = 40;
}

