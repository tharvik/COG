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
void windowResizingHandler(const int width, const int height);
void windowStatusHandler(const int state);
#ifdef __APPLE__
void windowClosingHandler();
#endif

// Keyboard handling
void keyboard(const int value);
void keyDown(const unsigned char key, const int x, const int y);
void specialKeyDown(const int key, const int x, const int y);
void keyUp(const unsigned char key, const int x, const int y);

// Mouse handling
void mouseHandler(const int button, const int state, const int x, const int y);
void motionHandler(const int width, const int height);
