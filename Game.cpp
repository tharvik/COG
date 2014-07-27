#include "Game.h"


Game::Game() : univers(), simulator(&univers)
{
        glClearColor(BGR_C);
        
        if (FULLSCREEN)
                glutFullScreen();
        
        
        setSimulator(&simulator);
        setUnivers(&univers);
        
	
	this->univers.addPlanet("test");
	
	
	Planet test("test");
	Planet asd("test");
	Planet asadf("test");
	//	Planet asdr("test");

	
	
	
	
	
        {
                glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
                glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
        }
        {
                glutReshapeFunc(windowResizingHandler);
                glutWindowStatusFunc(windowStatusHandler);
#ifdef __APPLE__
                glutWMCloseFunc(windowClosingHandler);
#endif
                glutDisplayFunc(displayHandler);
        }
}


void Game::enterMainMenu()
{
        glutSpecialFunc(specialKeyDown);
        glutKeyboardFunc(keyDown);
        glutKeyboardUpFunc(keyUp);
        
        glutMouseFunc(mouseHandler);
        glutMotionFunc(motionHandler);
        
        glutIdleFunc(tick);
        
        
        glutMainLoop();
}

void Game::enterPauseMenu()
{
}
