#pragma once

#include "opengl.h"

#include "config.h"
#include "Logger.h"
#include "Univers.h"

/**
 * Handle launching physic for Univers and calculus of FPS
 */
class Simulator {
	private:
		/**
		 * Univers it has to handle
		 */
		Univers *univers;

		/**
		 * Current computed FPS
		 */
		unsigned int FPS;

		/**
		 * Number of refresh since last FPS computation
		 */
		unsigned int refreshCounter;
		
		/**
		 * Number of ticks
		 */
		unsigned long long tickCounter = 0;

		/**
		 * Last \ref actualPhysic we reported
		 */
		unsigned int lastPhysicReport;

		/**
		 * Last physic we computed
		 */
		unsigned int lastPhysic;

		/**
		 * Currently computed physic
		 */
		unsigned int actualPhysic;

		/**
		 * Step of a physic computation, the less, the more accurate it
		 * will be
		 */
		double physicDelta;

		/**
		 * Update FPS and lastRefreshReport
		 */
		void measureFPS();

		/**
		 * Physic per second, number of physic computed in a second
		 */
		unsigned int PPS;

		/**
		 * Number of physic since last PPS computation
		 */
		unsigned int physicCounter;

		/**
		 * Last \ref actualRefresh we reported
		 */
		unsigned int lastRefreshReport;

		/**
		 * Last refresh we computed
		 */
		unsigned int lastRefresh;

		/**
		 * Current time of refresh
		 */
		unsigned int actualRefresh;

		/**
		 * Update PPS and lastPhysicReport
		 */
		void measurePPS();

	public:
		/**
		 * Construct an empty and invalid Simulator
		 */
		Simulator();

		/**
		 * Construct with the given Univers
		 *
		 * \param univers Univers to simulate
		 */
		Simulator(Univers *univers);

		/**
		 * Print FPS and PPS info to cout
		 */
		void printInfo() const;

		/**
		 * Refresh the simulation and forward to \ref univers
		 */
		void refresh();

		/**
		 * Compute physics and forward to \ref univers
		 */
		void physic();
};

void tick();
