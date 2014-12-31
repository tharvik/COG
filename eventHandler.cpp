#include "eventHandler.h"
#include <memory>

static std::set<int> keysPressed;
static Game* game;

using namespace std;

void setGame(Game* _game)
{
        game = _game;
}

// Window and display handling
void displayHandler()
{
        //universe->refresh(SWAP);
}

void windowResizingHandler(const int width, const int height)
{
        glViewport(0, 0, GLsizei(width), GLsizei(height));
}

void windowStatusHandler(const int state)
{
        switch (state) {
                case GLUT_HIDDEN:
                        logger_info("The window is hidden");
                        break;
                case GLUT_FULLY_RETAINED:
                        logger_info("The window is fully retained");
                        break;
                case GLUT_PARTIALLY_RETAINED:
                        logger_info("The window is partially retained");
                        break;
                case GLUT_FULLY_COVERED:
                        logger_info("The window is fully covered");
                        break;
		default:
                        logger_warn("The window is in an unknow state");
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
                keysPressed.erase('p');
        }
        if (keysPressed.count(27)) {
                glutDestroyWindow(1);
                exit(0);
        }

        for (const int key : keysPressed)
                game->event(unique_ptr<Event>(new KeyboardEvent(key)));

        for (int i = 1; i <= 20; i ++) // haha!
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

void tick()
{
        game->event(unique_ptr<Event>(new RefreshEvent(RefreshEvent::IMAGE |
                                                       RefreshEvent::LEVEL |
                                                       RefreshEvent::PHYSICS)));
}
