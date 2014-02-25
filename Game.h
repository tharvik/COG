#pragma once

#include "opengl.h"

#include "config.h"
#include "eventHandler.h"
#include "Logger.h"
#include "Simulator.h"
#include "Univers.h"

/**
 * Represent the whole Game
 */
class Game {
	private:
		/**
		 * The generated Univers
		 */
		Univers univers;

		/**
		 * The Simulator for the Univers
		 */
		Simulator simulator;

	public:
		/**
		 * Setup the Univers, the Simulator and some GLUT function
		 */
		Game();

		/**
		 * Enter the main menu
		 */
		static void enterMainMenu();

		/**
		 * Enter the pause menu
		 */
		static void enterPauseMenu();
};
