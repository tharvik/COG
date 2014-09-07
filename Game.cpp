#include "Game.h"


Game::Game() : univers(), simulator(&univers)
{
        glClearColor(BACKGROUND_COLOR);

        if (FULLSCREEN)
                glutFullScreen();
        
        
        setSimulator(&simulator);
        setUnivers(&univers);
        
	Vvector pos(0, 0, 0);
	
	this->univers.addPlanet("axe", pos);
	pos += Vvector(-5, -5, 0);
	this->univers.addPlanet("House", pos);
	
	
	glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
	glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
	
	glutReshapeFunc(windowResizingHandler);
	glutWindowStatusFunc(windowStatusHandler);
#ifdef __APPLE__
	glutWMCloseFunc(windowClosingHandler);
#endif
	glutDisplayFunc(displayHandler);
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
{}
