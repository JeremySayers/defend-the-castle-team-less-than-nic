/* 
 * File:   FireDefense.h
 * Author: Jeremy
 *
 * Created on May 1, 2014, 9:46 PM
 */

#include <SDL.h>

#ifndef FIREDEFENSE_H
#define	FIREDEFENSE_H

class FireDefense {
public:
    int amount;
    int currentAnimationFrame;
    FireDefense();
    SDL_Rect fireGuyRect;
    SDL_Rect amountRect;
private:

};

#endif	/* FIREDEFENSE_H */

