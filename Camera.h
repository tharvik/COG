#pragma once

#include "opengl.h"
#include <set>
#include <math.h>
#include <array>

#include "config.h"
#include "Logger.h"
#include "utilities.h"
#include "Vvector.h"

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
        
        // Movement vectors
	Vvector d;
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
	
	// Translations
        void move(GLdouble mov[]);
	void move(GLdouble movForward, GLdouble movSideward, GLdouble movUpward);
        
        void goTo(GLdouble oriX, GLdouble oriY, GLdouble oriZ);
        
        // Setters
        void setPositionX(GLdouble posX);
        void setPositionY(GLdouble posY);
        void setPositionZ(GLdouble posZ);
        
        void setOrientationX(GLdouble posX);
        void setOrientationY(GLdouble posY);
        void setOrientationZ(GLdouble posZ);
        
	// Getters
        GLdouble getPositionX();
        GLdouble getPositionY();
        GLdouble getPositionZ();
        
        GLdouble getOrientationX();
        GLdouble getOrientationY();
        GLdouble getOrientationZ();
        
        GLdouble getDirectionX();
        GLdouble getDirectionY();
        GLdouble getDirectionZ();
        
        // Keys handling
        void keyDown(std::set<int> &keysPressed);
        
        // Calculate next position
        void physic(double &physicDelta);
        
	// Place itself
        void look();
	
	// Destructor
        ~Camera();
};
