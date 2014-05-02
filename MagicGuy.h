/* 
 * File:   MagicGuy.h
 * Author: Jeremy
 *
 * Created on May 1, 2014, 10:43 PM
 */
#include <SDL.h>

#ifndef MAGICGUY_H
#define	MAGICGUY_H

class MagicGuy {
public:
    int amount;
    int currentAnimationFrame;
    MagicGuy();
    SDL_Rect magicGuyRect;
    SDL_Rect amountRect;
private:

};

#endif	/* MAGICGUY_H */

