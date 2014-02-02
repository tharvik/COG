//
//  Camera.cpp
//  COG
//
//  Created by Vianney Rousset on 31.01.14.
//

#include <iostream>
#include "Camera.h"
#include "opengl.h"

Camera::Camera(GLdouble posX, GLdouble posY, GLdouble posZ,
	   GLdouble phi, GLdouble teta, GLdouble psi)
{
	p[0] = posX;
	p[1] = posY;
	p[2] = posZ;
	
	upVector[0] = 0;
	upVector[1] = 0;
	upVector[2] = 1;
	
	angle[0] = phi;
	angle[1] = teta;
	angle[2] = psi;
	
	angleToDirection();
}

void Camera::angleToDirection()
{
	v[0] = cos(angle[1]) * cos(angle[0]);
	v[1] = cos(angle[1]) * sin(angle[0]);
	v[2] = sin(angle[1]);
}

void Camera::rotateX(GLdouble alpha)
{
	angle[2] += alpha;
}

void Camera::rotateY(GLdouble alpha)
{
	angle[0] += alpha;
	angleToDirection();
}

void Camera::rotateZ(GLdouble alpha)
{
	angle[1] += alpha;
	angleToDirection();
}

void Camera::forwardBackward(GLdouble l)
{
	p[0] += v[0] * l;
	p[1] += v[1] * l;
	p[2] += v[2] * l;
}

void Camera::plant()
{
	gluLookAt(p[0], p[1], p[2], p[0] + v[0], p[1] + v[1], p[2] + v[2], upVector[0], upVector[1], upVector[2]);
}