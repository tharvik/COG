#pragma once

#include "opengl.h"
#include <set>
#include <string>

#include "Camera.h"
#include "config.h"
#include "Light.h"
#include "Object.h"
#include "Planet.h"

#ifdef __APPLE__
#	include <memory.h>
#else
#	include <memory>
#endif

#define perspective() gluPerspective(FOV,GLdouble(glutGet(GLUT_WINDOW_WIDTH)/\
        glutGet(GLUT_WINDOW_HEIGHT)),NEAREST,FAREST)

/**
 * The whole Univers
 */
class Univers {
private:
        /**
         * Set of Object the Univers has to draw
         */
        std::set<std::unique_ptr<Object>> objects;

        /**
         * Camera of this Univers
         */
        Camera camera;

        /**
         * Main Light
         */
        Light mainLight;

        /**
         * Draw every Object of \ref objects
         */
        void draw() const;
public:

	/**
	 * Enum used with the refresh function, to know what is needed to be
	 * recomputed
	 */
	typedef enum
	{
		NONE  = 0,	/**< no flags **/
		LEVEL = 1	/**< recalculate object mesh levels **/
	} universRefreshFlags;

        /**
         * Construct with default Camera and the \ref mainLight as a
         * carefully chosen position
         *
         * \todo Why this position for \ref Univers.mainLight?
         */
        Univers();

        /**
         * Construct with the given parameters for \ref camera
         *
         * \param posX Position on x
         * \param posY Position on y
         * \param posZ Position on z
         * \param anglePhi Orientation on x
         * \param angleTeta Orientation on y
         * \param anglepsi Orientation on z
         */
        Univers(const GLdouble posX, const GLdouble posY, const GLdouble posZ,
                const GLdouble anglePhi, const GLdouble angleTeta,
                const GLdouble anglepsi);


	/**
	 * Add a new planet, with the given name, to the \ref objects
	 *
	 * \param name	The name of the planet to create
	 *
	 * \return The previous size of \ref objects
	 */
        size_t addPlanet(const std::string& name);

	/**
	 * Add a new planet, with the given name and position, to the
	 * \ref objects
	 *
	 * \param name	The name of the planet to create
	 * \param pos	The position of the planet to create
	 *
	 * \return The previous size of \ref objects
	 */
        size_t addPlanet(const std::string& name, Vvector pos);

        /**
         * Print some information about the \ref camera
         */
        void printInfo() const;

        /**
         * Handle events from GLUT, mainly forwarded to \ref camera
         *
         * \param keysPressed Currently pressed keys
         */
        void keyboard(std::set<int> &keysPressed);

        /**
         * Reset the perspective, draw the camera and the \ref objects
	 *
	 * \param flags	The type of refresh to do
         */
        void refresh(universRefreshFlags flags);

        /**
         * Handle physic inside the Univers, mainyl forwarded to
         * \ref camera
         *
         * \param physicDelta Delta of physic to compute
         */
        void physic(double& physicDelta);
};
