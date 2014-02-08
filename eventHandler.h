#pragma once

#include <iostream>
#include <map>
#include "opengl.h"
#include <string>

#include "config.h"
#include "Game.h"
#include "Logger.h"
#include "Simulator.h"
#include "Univers.h"

#define repeatKey if (keysPressed[key])\
                        glutTimerFunc(KEY_REPEAT_PERIOD, keyboardHandler, key);

void displayHandler();
void windowResizingHandler(int width, int height);
void windowStatusHandler(int state);
#ifdef __APPLE__
void windowClosingHandler();
#endif

void keyboard(int value);
void keyDown(unsigned char key, int x, int y);
void specialKeyDown(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);

void mouseHandler(int button, int state, int x, int y);
void motionHandler(int width, int height);

void setSimulator(Simulator* theSimulator);
void setUnivers(Univers* theUnivers);
//void setGame(Game* theGame);