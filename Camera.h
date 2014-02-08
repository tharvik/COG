#pragma once

#include <iostream>
#include <map>
#include <math.h>

#include "config.h"
#include "Logger.h"
#include "opengl.h"
#include "utilities.h"

class Camera {
private:
        
	// position vector
	GLdouble p[3];
        
	// orientation vector
	GLdouble o[3];
        
        // movement vectors
        GLdouble d[3];
        GLdouble r[3];
        
        // for calculs
        GLdouble s[3];
        
public:
	// constructor
        Camera();
        Camera(GLdouble posX, GLdouble posY, GLdouble posZ,
               GLdouble oriX, GLdouble oriY, GLdouble oriZ);
        
	// rotations
	void rotate(GLdouble alpha, GLdouble beta);
        
        void lookTo(GLdouble posX, GLdouble posY, GLdouble posZ);
	
	// translations
        void move(GLdouble mov[]);
	void move(GLdouble movForward, GLdouble movSideward, GLdouble movUpward);
        
        void goTo(GLdouble oriX, GLdouble oriY, GLdouble oriZ);
        
        // setters
        void setPositionX(GLdouble posX);
        void setPositionY(GLdouble posY);
        void setPositionZ(GLdouble posZ);
        
        void setOrientationX(GLdouble posX);
        void setOrientationY(GLdouble posY);
        void setOrientationZ(GLdouble posZ);
        
	// getters
        GLdouble getPositionX();
        GLdouble getPositionY();
        GLdouble getPositionZ();
        
        GLdouble getOrientationX();
        GLdouble getOrientationY();
        GLdouble getOrientationZ();
        
        GLdouble getDirectionX();
        GLdouble getDirectionY();
        GLdouble getDirectionZ();
	
        void keyDown(std::map<int, bool> &keysPressed);
        
        // calculate next position
        void physic(double &physicDelta);
        
	// send the camera informations to OpenGL
        void look();
	
	// destructor
        ~Camera();
};