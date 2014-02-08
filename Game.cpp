#include "Game.h"

Game::Game() : univers(), simulator(&univers)
{
        glClearColor(BGR_C);
        
        if (FULLSCREEN)
                glutFullScreen();
        
        univers.addObject("Resources/Test files/mountain.obj", "Resources/Test files/mountain.png"); // To remove
        
        setSimulator(&simulator);
        setUnivers(&univers);
        
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
        
        enterMainMenu();
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