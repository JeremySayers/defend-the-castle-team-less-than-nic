/* 
 * File:   InstructionsScreen.h
 * Author: Jeremy
 *
 * Created on May 2, 2014, 3:43 AM
 */

#include "GraphicsRenderer.h"
#include <string>
#include <stdio.h>

#ifndef INSTRUCTIONSSCREEN_H
#define	INSTRUCTIONSSCREEN_H

class InstructionsScreen {
public:
    InstructionsScreen(GraphicsRenderer);
    void render();
    bool loadMedia();
private:
    std::string exePath();

};

#endif	/* INSTRUCTIONSSCREEN_H */

