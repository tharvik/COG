#pragma once

#include "opengl.h"

#include "config.h"
#include "eventHandler.h"
#include "Logger.h"
#include "Simulator.h"
#include "Univers.h"

class Game {
private:
        Univers univers;
        Simulator simulator;
        
public:
        // Constructor
        Game();
        
        // Game modes
        void enterMainMenu();
        void enterPauseMenu();
        
        // Destructor
        ~Game();
};