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
		Camera(const GLdouble posX, const GLdouble posY,
				const GLdouble posZ, const GLdouble oriX,
				const GLdouble oriY, const GLdouble oriZ);

		/**
		 * Rotate from the angle
		 *
		 * \param alpha Angle in radian to move on the horizontal plan
		 * \param beta Angle in radian to move on the vertical plan
		 */
		void rotate(const GLdouble alpha, const GLdouble beta);

		/**
		 * Look at the given point
		 *
		 * \param posX Position on x
		 * \param posY Position on y
		 * \param posZ Position on z
		 */
		void lookTo(const GLdouble posX, const GLdouble posY,
				const GLdouble posZ);

		/**
		 * Begin a move of the given values
		 *
		 * \param movForward Move forward of this much
		 * \param movSideward Move sideway of this much
		 * \param movUpward Move upward of this much
		 */
		void move(const GLdouble movForward, const GLdouble movSideward,
				const GLdouble movUpward);

		/**
		 * Begin a move to the given position
		 *
		 * \param oriX X position to go to
		 * \param oriY Y position to go to
		 * \param oriZ Z position to go to
		 */
		void goTo(const GLdouble oriX, const GLdouble oriY,
				const GLdouble oriZ);

		/**
		 * Set the x position
		 *
		 * \param posX New x value
		 */
		void setPositionX(const GLdouble posX);

		/**
		 * Set the y position
		 *
		 * \param posY New y value
		 */
		void setPositionY(const GLdouble posY);

		/**
		 * Set the z position
		 *
		 * \param posZ New z value
		 */
		void setPositionZ(const GLdouble posZ);

		/**
		 * Set the x orientation
		 *
		 * \param posX New x value
		 */
		void setOrientationX(const GLdouble posX);

		/**
		 * Set the y orientation
		 *
		 * \param posY New y value
		 */
		void setOrientationY(const GLdouble posY);

		/**
		 * Set the z orientation
		 *
		 * \param posZ New z value
		 */
		void setOrientationZ(const GLdouble posZ);

		/**
		 * get the camera position
		 *
		 * \return position
		 */
		const Vvector& getPosition() const;

		/**
		 * Return the x position
		 *
		 * \return X position
		 */
		GLdouble getPositionX() const;

		/**
		 * Return the y position
		 *
		 * \return Y position
		 */
		GLdouble getPositionY() const;

		/**
		 * Return the z position
		 *
		 * \return Z position
		 */
		GLdouble getPositionZ() const;

		/**
		 * Return the x orientation
		 *
		 * \return X orientation
		 */
		GLdouble getOrientationX() const;

		/**
		 * Return the y orientation
		 *
		 * \return Y orientation
		 */
		GLdouble getOrientationY() const;

		/**
		 * Return the z orientation
		 *
		 * \return Z orientation
		 */
		GLdouble getOrientationZ() const;

		/**
		 * Return the x direction
		 *
		 * \return X direction
		 */
		GLdouble getDirectionX() const;

		/**
		 * Return the y direction
		 *
		 * \return Y direction
		 */
		GLdouble getDirectionY() const;

		/**
		 * Return the z direction
		 *
		 * \return Z direction
		 */
		GLdouble getDirectionZ() const;

		/**
		 * Handle keydowns from GLUT
		 *
		 * \param keysPressed Set of key currently down
		 */
		void keyDown(std::set<int> &keysPressed);

		/**
		 * Calculate the next position
		 *
		 * \param physicDelta Relative move to compute by step, the smaller, the
		 * more it will be but the more call it will need
		 */
		void physic(const double &physicDelta);

		/**
		 * Launch gluLookAt with the current state
		 */
		void look();
};
