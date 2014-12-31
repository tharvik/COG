#include "Game.h"

#include <LinearMath/btVector3.h>

Universe Game::universe;
Renderer Game::renderer;

using namespace std;

void Game::configureGLUT() // Deprecated
{
        glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
        glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
        glutReshapeFunc(windowResizingHandler);
        glutWindowStatusFunc(windowStatusHandler);
#ifdef __APPLE__
        glutWMCloseFunc(windowClosingHandler);
#endif
        glutDisplayFunc(displayHandler);
        
        glutSpecialFunc(specialKeyDown);
        glutKeyboardFunc(keyDown);
        glutKeyboardUpFunc(keyUp);
        
        glutMouseFunc(mouseHandler);
        glutMotionFunc(motionHandler);
        
        glutIdleFunc(tick);
        
        setGame(this);
}

Game::Game()
{
        glClearColor(BACKGROUND_COLOR);
        
        configureGLUT();
        glutMainLoop();
}

void Game::event(const unique_ptr<Event>& event)
{
        if (event->getType() == Event::REFRESH) {
                if (((const unique_ptr<RefreshEvent>&) event)->getRefreshType()
                                                          & RefreshEvent::IMAGE)
                        renderer.render();
//                if (((const unique_ptr<RefreshEvent>&) event)->getRefreshType()
//                                                          & RefreshEvent::LEVEL)
//                        universe.calculateLevel(cameras[0]); // TODO ask Vianney
                
                if (((const unique_ptr<RefreshEvent>&) event)->getRefreshType()
                                                        & RefreshEvent::PHYSICS)
                        universe.physics(0.1); // TODO ask Antonin
        }
        
        universe.event(event);
//        interface.event(event);
}
