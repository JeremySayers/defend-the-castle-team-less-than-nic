/* 
 * File:   EnemyOne.h
 * Author: Jeremy
 * Created on April 29, 2014, 6:43 PM
 */


#include <SDL.h>

#ifndef ENEMYONE_H
#define	ENEMYONE_H

class EnemyOne {
public:
    EnemyOne();
    int health;
    int currentAnimationFrame;
    bool walkAnim;
    bool attackAnim;
    bool active;
    SDL_Rect enemyRect;
    
    void incrementAnimationFrame();
    void resetAnimationFrame();
private:

};

#endif	/* ENEMYONE_H */

