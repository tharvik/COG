#include <iostream>
#include "opengl.h"
#include <string>

#include "config.h"
#include "eventHandler.h"
#include "Simulator.h"
#include "Sphere.h"

int initLibraries(int *argc, char *argv[]);

void openWindow(int &&x, int &&y, int &&width, int &&height, std::string &&title);

void setUpOpenGL();
void setUpScene(Univers &univers);

int main(int argc, char *argv[])
{
        initLibraries(&argc, argv);
        
        if (GAME_MODE)
                glutEnterGameMode();
        else
                openWindow(WIN_X, WIN_Y, WIN_W, WIN_H, WIN_T);
        
        Univers univers;
        setUpScene(univers);
        univers.addObject("Resources/Test files/mountain.obj", "Resources/Test files/mountain.png");
        
        Simulator simulator = Simulator(&univers);
        /*Sphere sphere;
        univers.addSphere(sphere);*/
        
        setSimulator(&simulator);
        setUnivers(&univers);
        
        {
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
                
                glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
        }
        
        glutMainLoop();
                
	return 0;
}

/*
 * Initialize the following libraries:
 * - GLUT
 * - SDL
 */
int initLibraries(int *argc, char *argv[])
{
        // GLUT library
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
        
        return true;
}

/*
 * Open a new window
 * The window is not revealed
 */
void openWindow(int &&x, int &&y, int &&width, int &&height, std::string &&title)
{
        glutInitWindowSize(width, height);
        glutInitWindowPosition(x, y);
        glutCreateWindow(title.c_str());
        glutHideWindow();
        
        if (FULLSCREEN)
                glutFullScreen();
}

/*
 * Set the background color
 * Create univers
 * Place camera
 * Start the FPS
 * Start the simulation timer
 */
void setUpScene(Univers& univers)
{
        setUpOpenGL();
        
        glClearColor(BGR_C);
}
void setUpOpenGL()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);
        gluPerspective(60, (GLdouble) glutGet(GLUT_WINDOW_WIDTH) /
                       glutGet(GLUT_WINDOW_HEIGHT), 0.1, 1000);
}