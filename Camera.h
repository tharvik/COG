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
	// Position vector
	Vvector p;
        
	// Orientation vector
	Vvector o;
        
        // Movement vectors
	Vvector d;
	Vvector r;
        
        // For calculs
	Vvector s;
        
public:
	// Constructors
        Camera();
        Camera(GLdouble posX, GLdouble posY, GLdouble posZ,
               GLdouble oriX, GLdouble oriY, GLdouble oriZ);
        
	// Rotations
	void rotate(GLdouble alpha, GLdouble beta);
        
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
