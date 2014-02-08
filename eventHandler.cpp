#include "eventHandler.h"

static std::map<int, bool> keysPressed = std::map<int, bool>();
static Simulator* simulator = nullptr;
static Univers* univers = nullptr;

void keyDown(unsigned char key, int x, int y)
{
        keysPressed[key] = true;
}

void specialKeyDown(int key, int x, int y)
{
        keysPressed[key + 255] = true;
}

void keyUp(unsigned char key, int x, int y)
{
        keysPressed[key] = false;
}

void keyboard(int value)
{
        if (keysPressed['f']) {
                if (glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT)
                    && glutGet(GLUT_WINDOW_WIDTH ) == glutGet(GLUT_SCREEN_WIDTH)) {
                        glutReshapeWindow(WIN_W, WIN_H);
                        glutPositionWindow(WIN_X, WIN_Y);
                } else {
                        glutFullScreen();
                }
                keysPressed['f'] = false;
        }
        if (keysPressed['p']) {
                simulator->printInfo();
                keysPressed['p'] = false;
        }
        if (keysPressed[27] ) {
                glutDestroyWindow(1);
                exit(0);
        }
        
        univers->keyboard(keysPressed);
        
        for (int i = 1; i <= 20; i ++)
                keysPressed[255 + i] = false; // To improve
        
        glutTimerFunc(KEY_REPEAT_PERIOD, keyboard, 0);
}

void mouseHandler(int button, int state, int x, int y)
{
        // click, click...
}

void motionHandler(int width, int height)
{
        // drag...
}

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

void setSimulator(Simulator* theSimulator)
{
        simulator = theSimulator;
}

void setUnivers(Univers* theUnivers)
{
        univers = theUnivers;
}