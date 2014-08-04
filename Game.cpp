#include "Game.h"


Game::Game() : univers(), simulator(&univers)
{
        glClearColor(BGR_C);
        
        if (FULLSCREEN)
                glutFullScreen();
        
        
        setSimulator(&simulator);
        setUnivers(&univers);
        
	Vvector pos(0, 0, 0);
	Vvector addx(5, 0, 0);
	Vvector addy(0, 5, 0);
	
	for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
		this->univers.addPlanet("Torus", pos);
		pos += addx;
	}
		pos = Vvector(0, pos.y() + addy.y(), pos.z());
	}
	
	

	
	
	
	
	
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
