#include "Simulator.h"

static Simulator *self;

// Constructors
Simulator::Simulator() :
	univers(nullptr), FPS(0), refreshCounter(REPORT_FPS), tickCounter(0),
	lastPhysicReport(0), lastPhysic(0), actualPhysic(0), PPS(0),
	physicCounter(REPORT_PPS), lastRefreshReport(0), lastRefresh(0),
	actualRefresh(0), physicDelta(0)
{
        self = this;
}

Simulator::Simulator(Univers *theUnivers) :
	univers(theUnivers), FPS(0), refreshCounter(REPORT_FPS), tickCounter(0),
	lastPhysicReport(0), lastPhysic(0), actualPhysic(0), PPS(0),
	physicCounter(REPORT_PPS), lastRefreshReport(0), lastRefresh(0),
	actualRefresh(0), physicDelta(0)
{
        self = this;
}

void Simulator::printInfo() const
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
	int get = glutGet(GLUT_ELAPSED_TIME);
	if(get < 0) {
		logger_warn("Unable to get elapsed time");
		return;
	} else {
		actualPhysic = (unsigned int) get;
	}

        physicDelta = double(MINIMUM_PPS * (actualPhysic - lastPhysic) / 1000.0);

        if (physicDelta > 1) {
                physicDelta = 1;
                logger_warn("Lag occured"); // To manage
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
	int get = glutGet(GLUT_ELAPSED_TIME);
	if(get < 0) {
		logger_warn("Unable to get elapsed time");
		return;
	} else {
		actualRefresh = (unsigned int) get;
	}
        
        if (refreshCounter >= REPORT_FPS) {
                measureFPS();
                refreshCounter = 0;
        }
	
	if (!(tickCounter % 10))
		univers->refresh(Univers::LEVEL);
	else
		univers->refresh(Univers::NONE);
        
        refreshCounter++;
	tickCounter++;
        lastRefresh = actualRefresh;
}

void Simulator::measureFPS()
{
        FPS = (1000 * REPORT_FPS) / (actualRefresh - lastRefreshReport);
        lastRefreshReport = actualRefresh;
}

void tick()
{
        self->physic();
        self->refresh();
}
