#pragma once

#include <map>
#include "opengl.h"
#include <set>
#include <string>

#include "config.h"
#include "Game.h"
#include "Logger.h"
#include "Simulator.h"
#include "Univers.h"

#define repeatKey if (keysPressed[key])\
                        glutTimerFunc(KEY_REPEAT_PERIOD, keyboardHandler, key);

// Initialisation
void setSimulator(Simulator* theSimulator);
void setUnivers(Univers* theUnivers);
//void setGame(Game* theGame);

// Window and display handling
void displayHandler();
void windowResizingHandler(int width, int height);
void windowStatusHandler(int state);
#ifdef __APPLE__
void windowClosingHandler();
#endif

// Keyboard handling
void keyboard(int value);
void keyDown(unsigned char key, int x, int y);
void specialKeyDown(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);

// Mouse handling
void mouseHandler(int button, int state, int x, int y);
void motionHandler(int width, int height);