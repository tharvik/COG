//
//  Camera.h
//  COG
//
//  Created by Vianney Rousset on 31.01.14.
//

#ifndef COG_Camera_h
#define COG_Camera_h

#include <math.h>
#include "opengl.h"

class Camera {
private:

	// position vector of the camera
	GLdouble p[3];
	
	// direction vector of the camera
	GLdouble v[3];
	
	GLdouble upVector[3];
	
	// direction angle of the camera {phi, teta}
	GLdouble angle[3];
	
	// calculate
	void angleToDirection();
	void DirectionToAngle();
		
public:
	
	// constructor
	Camera(GLdouble pX = 1, GLdouble pY = 1, GLdouble pZ = 1,
		   GLdouble phi = 0, GLdouble teta = 0, GLdouble psi = 0);

	// getters
	GLdouble* getPosition();
	GLdouble* getLookPoint();
	GLdouble* getAngle();
		
	// rotations
	void rotateX(GLdouble alpga);
	void rotateY(GLdouble alpha);
	void rotateZ(GLdouble alpha);
	
	// translations
	void forwardBackward(GLdouble l);
	void RightLeft(GLdouble l);
	
	// send the camera informations to OpenGL
	void plant();
	
	// setters
	
	// destructor

};

#endif
