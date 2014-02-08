#pragma once

#include <iostream>
#include "opengl.h"

#include "config.h"
#include "eventHandler.h"
#include "Simulator.h"
#include "Univers.h"

class Game {
private:
        Univers univers;
        Simulator simulator;
        
public:
        // Constructors
        Game();
        
        // Game modes
        void enterMainMenu();
        void enterPauseMenu();
};