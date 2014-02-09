#include "Simulator.h"

static Simulator *self;

// Constructors
Simulator::Simulator()
{
        self = this;
        physicCounter = REPORT_PPS;
        refreshCounter = REPORT_FPS;
}

Simulator::Simulator(Univers *theUnivers)
{
        univers = theUnivers;
        self = this;
        physicCounter = REPORT_PPS;
        refreshCounter = REPORT_FPS;
}

void Simulator::printInfo()
{
        std::cout << "FPS:"
                        << FPS
                        << std::endl
                  << "PPS:"
                        << PPS
                        << std::endl;
        
        univers->printInfo();
}

void Simulator::physic()
{
        actualPhysic = glutGet(GLUT_ELAPSED_TIME);
        physicDelta = (double) MINIMUM_PPS * (actualPhysic - lastPhysic) / 1000;
        
        if (physicDelta > 1) {
                physicDelta = 1;
                logger::warn("Lag occured", FL); // To manage
        }
        if (physicCounter >= REPORT_PPS) {
                measurePPS();
                physicCounter = 0;
        }
        
        univers->physic(physicDelta);
        
        physicCounter ++;
        lastPhysic = actualPhysic;
}

void Simulator::measurePPS()
{
        PPS = (1000 * REPORT_PPS) / (actualPhysic - lastPhysicReport);
        lastPhysicReport = actualPhysic;
}

void Simulator::refresh()
{
        actualRefresh = glutGet(GLUT_ELAPSED_TIME);
        
        if (refreshCounter >= REPORT_FPS) {
                measureFPS();
                refreshCounter = 0;
        }
        
        univers->refresh();
        
        refreshCounter ++;
        lastRefresh = actualRefresh;
}

void Simulator::measureFPS()
{
        FPS = (1000 * REPORT_FPS) / (actualRefresh - lastRefreshReport);
        lastRefreshReport = actualRefresh;
}

// Destructors
Simulator::~Simulator()
{}

void tick()
{
        self->physic();
        self->refresh();
}