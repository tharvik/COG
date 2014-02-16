#include "Game.h"

// Constructor
Game::Game() : univers(), simulator(&univers)
{
        glClearColor(BGR_C);
        
        if (FULLSCREEN)
                glutFullScreen();
        
        univers.addObject("mountain");
        
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

// Game modes
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

// Destructor
Game::~Game()
{}