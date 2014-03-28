/* 
 * File:   MenuScreen.h
 * Author: jsayers
 *
 * Created on March 28, 2014, 2:10 PM
 */

#include "GraphicsRenderer.h"
#include <string>
#include <stdio.h>

#ifndef MENUSCREEN_H
#define	MENUSCREEN_H

class MenuScreen {
    public:
        MenuScreen(GraphicsRenderer);
        void render();
        bool loadMedia();
    private:
        std::string exePath();

};

#endif	/* MENUSCREEN_H */

