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

void windowResizingHandler(const int width, const int height)
{
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void windowStatusHandler(const int state)
{
        switch (state) {
                case GLUT_HIDDEN:
                        logger::info("The window is hidden", _FL_);
                        break;
                case GLUT_FULLY_RETAINED:
                        logger::info("The window is fully retained", _FL_);
                        break;
                case GLUT_PARTIALLY_RETAINED:
                        logger::info("The window is partially retained", _FL_);
                        break;
                case GLUT_FULLY_COVERED:
                        logger::info("The window is fully covered", _FL_);
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
void keyDown(const unsigned char key, const int x, const int y)
{
        keysPressed.insert(key);
}

void specialKeyDown(const int key, const int x, const int y)
{
        keysPressed.insert(key + 255);
}

void keyUp(const unsigned char key, const int x, const int y)
{
        if (key >= 'a' && key <= 'z') {
                keysPressed.erase(key);
                keysPressed.erase(key - ' ');
        } else if (key >= 'A' && key <= 'Z') {
                keysPressed.erase(key);
                keysPressed.erase(key + ' ');
        }
}

void keyboard(const int value)
{
        if (keysPressed.count('f')) {
                if (glutGet(GLUT_WINDOW_HEIGHT) == glutGet(GLUT_SCREEN_HEIGHT)
                    && glutGet(GLUT_WINDOW_WIDTH ) == glutGet(GLUT_SCREEN_WIDTH)) {
                        glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
                        glutPositionWindow(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y);
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
void mouseHandler(const int button, const int state, const int x, const int y)
{
        // click, click...
}

void motionHandler(const int width, const int height)
{
        // drag...
}
