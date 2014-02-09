#pragma once

#include "opengl.h"

#include "config.h"
#include "Logger.h"
#include "Univers.h"

class Simulator {
private:
        Univers *univers = nullptr;
        
        unsigned int FPS;
        unsigned int refreshCounter = 0;
        
        unsigned int lastPhysicReport;
        unsigned int lastPhysic;
        unsigned int actualPhysic;
        double physicDelta;
        
        void measureFPS();
        
        unsigned int PPS;
        unsigned int physicCounter = 0;
        
        unsigned int lastRefreshReport;
        unsigned int lastRefresh;
        unsigned int actualRefresh;
        
        void measurePPS();
        
public:
        // Constructors
        Simulator();
        Simulator(Univers *univers);
        
        void printInfo();
        
        void refresh();
        void physic();
        
        // Destructors
        ~Simulator();
};

void tick();