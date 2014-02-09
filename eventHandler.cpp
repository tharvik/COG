#include "eventHandler.h"

static Game* game = nullptr;
static Simulator* simulator = nullptr;
static Univers* univers = nullptr;

static std::set<int> keysPressed;

// Initialisation
/*void setGame(Game* theGame)
 {
 game = theGame;
 }*/

void setSimulator(Simulator* theSimulator)
{
        simulator = theSimulator;
}

void setUnivers(Univers* theUnivers)
{
        univers = theUnivers;
}

// Window and display handling
void displayHandler()
{
        //univers->refresh(SWAP);
}

void windowResizingHandler(int width, int height)
{
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void windowStatusHandler(int state)
{
        switch (state) {
                case GLUT_HIDDEN:
                        logger::info("The window is hidden", FL);
                        break;
                case GLUT_FULLY_RETAINED:
                        logger::info("The window is fully retained", FL);
                        break;
                case GLUT_PARTIALLY_RETAINED:
                        logger::info("The window is partially retained", FL);
                        break;
                case GLUT_FULLY_COVERED:
                        logger::info("The window is fully covered", FL);
                        break;
        }
}

#ifdef __APPLE__
void windowClosingHandler()
{
        glutDestroyWindow(1);
        exit(0);
}
#endif

// Keyboard handling
void keyDown(unsigned char key, int x, int y)
{
        keysPressed.insert(key);
}

void specialKeyDown(int key, int x, int y)
{
        keysPressed.insert(key + 255);
}

#include <iostream>

void keyUp(unsigned char key, int x, int y)
{
        if (key >= 'a' && key <= 'z') {
                keysPressed.erase(key);
                keysPressed.erase(key - ' ');
        } else if (key >= 'A' && key <= 'Z') {
                keysPressed.erase(key);
                keysPressed.erase(key + ' ');
        }
}

void keyboard(int value)
{
        if (keysPressed.count('f')) {
                if (glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT)
                    && glutGet(GLUT_WINDOW_WIDTH ) == glutGet(GLUT_SCREEN_WIDTH)) {
                        glutReshapeWindow(WIN_W, WIN_H);
                        glutPositionWindow(WIN_X, WIN_Y);
                } else {
                        glutFullScreen();
                }
                keysPressed.erase('f');
        }
        if (keysPressed.count('p')) {
                simulator->printInfo();
                keysPressed.erase('p');
        }
        if (keysPressed.count(27)) {
                glutDestroyWindow(1);
                exit(0);
        }
        
        univers->keyboard(keysPressed);
        
        for (int i = 1; i <= 20; i ++)
                keysPressed.erase(255 + i);
        
        glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
}

// Mouse handling
void mouseHandler(int button, int state, int x, int y)
{
        // click, click...
}

void motionHandler(int width, int height)
{
        // drag...
}