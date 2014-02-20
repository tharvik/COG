#pragma once

#include "opengl.h"
#include <set>
#include <math.h>
#include <array>

#include "config.h"
#include "Logger.h"
#include "utilities.h"
#include "Vvector.h"

/**
 * Handle the Camera for OpenGL
 */
class Camera {
	private:
		/**
		 * Current position
		 */
		Vvector p;

		/**
		 * Current orientation
		 */
		Vvector o;

		/**
		 * Inertia Vvector of deplacement
		 */
		Vvector d;

		/**
		 * Inertia Vvector of rotation
		 */
		Vvector r;

		// For calculs
		Vvector s;

	public:
		/**
		 * Construct with the default values in config.h
		 *
		 * \ref p is initialized with POS_* from config.h\n
		 * \ref o and \ref r are initstate with ORI_* from config.h and
		 * normalized\n
		 * \ref d is set to zero\n
		 */
		Camera();

		/**
		 * Construct with the given values
		 *
		 * \param posX Position on x
		 * \param posY Position on y
		 * \param posZ Position on z
		 * \param oriX Orientation on x
		 * \param oriY Orientation on y
		 * \param oriZ Orientation on z
		 */
		Camera(GLdouble posX, GLdouble posY, GLdouble posZ,
				GLdouble oriX, GLdouble oriY, GLdouble oriZ);

		// Rotations
		void rotate(GLdouble alpha, GLdouble beta);

		/**
		 * Look at the given point
		 *
		 * \param posX Position on x
		 * \param posY Position on y
		 * \param posZ Position on z
		 */
		void lookTo(GLdouble posX, GLdouble posY, GLdouble posZ);

		/**
		 * Begin a move of the given values
		 *
		 * \param movForward Move forward of this much
		 * \param movSideward Move sideway of this much
		 * \param movUpward Move upward of this much
		 */
		void move(GLdouble movForward, GLdouble movSideward, GLdouble movUpward);

		/**
		 * Begin a move to the given position
		 *
		 * \param oriX X position to go to
		 * \param oriY Y position to go to
		 * \param oriZ Z position to go to
		 */
		void goTo(GLdouble oriX, GLdouble oriY, GLdouble oriZ);

		/**
		 * Set the x position
		 *
		 * \param posX New x value
		 */
		void setPositionX(GLdouble posX);

		/**
		 * Set the y position
		 *
		 * \param posY New y value
		 */
		void setPositionY(GLdouble posY);

		/**
		 * Set the z position
		 *
		 * \param posZ New z value
		 */
		void setPositionZ(GLdouble posZ);

		/**
		 * Set the x orientation
		 *
		 * \param posX New x value
		 */
		void setOrientationX(GLdouble posX);

		/**
		 * Set the y orientation
		 *
		 * \param posY New y value
		 */
		void setOrientationY(GLdouble posY);

		/**
		 * Set the z orientation
		 *
		 * \param posZ New z value
		 */
		void setOrientationZ(GLdouble posZ);

		/**
		 * Return the x position
		 *
		 * \return X position
		 */
		GLdouble getPositionX();

		/**
		 * Return the y position
		 *
		 * \return Y position
		 */
		GLdouble getPositionY();

		/**
		 * Return the z position
		 *
		 * \return Z position
		 */
		GLdouble getPositionZ();

		/**
		 * Return the x orientation
		 *
		 * \return X orientation
		 */
		GLdouble getOrientationX();

		/**
		 * Return the y orientation
		 *
		 * \return Y orientation
		 */
		GLdouble getOrientationY();

		/**
		 * Return the z orientation
		 *
		 * \return Z orientation
		 */
		GLdouble getOrientationZ();

		/**
		 * Return the x direction
		 *
		 * \return X direction
		 */
		GLdouble getDirectionX();

		/**
		 * Return the y direction
		 *
		 * \return Y direction
		 */
		GLdouble getDirectionY();

		/**
		 * Return the z direction
		 *
		 * \return Z direction
		 */
		GLdouble getDirectionZ();

		/**
		 * Handle keydowns from GLUT
		 *
		 * \param keysPressed Set of key currently down
		 */
		void keyDown(std::set<int> &keysPressed);

		// Calculate next position
		void physic(double &physicDelta);

		/**
		 * Launch gluLookAt with the current state
		 */
		void look();
};
