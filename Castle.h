/* 
 * File:   Castle.h
 * Author: Jeremy
 *
 * Created on May 1, 2014, 8:23 PM
 */
#include <SDL.h>
#ifndef CASTLE_H
#define	CASTLE_H

class Castle {
public:
    Castle();
    int health;
    int healthMax;
    SDL_Rect healthBarBG;
    SDL_Rect healthBarFG;
    
    void calcHealthBarFGWidth();
private:

};

#endif	/* CASTLE_H */

