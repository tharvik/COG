#include "Camera.h"

#include <math.h>

// Constructors
Camera::Camera()
{
        p[0] = POS_X; p[1] = POS_Y; p[2] = POS_Z;
        o[0] = ORI_X; o[1] = ORI_Y; o[2] = ORI_Z;
        
        
	this->d.setNull();
	this->o.normalize();
	this->r = this->o;
}

Camera::Camera(GLdouble posX, GLdouble posY, GLdouble posZ,
               GLdouble oriX, GLdouble oriY, GLdouble oriZ)
{
        if (!oriX && !oriY && !oriZ) {
                logger::warn("The orientation vector given to the camera was of\
                             length 0", FL);
                oriX = 1;
        }
        p[0] = posX; p[1] = posY; p[2] = posZ;
        o[0] = oriX; o[1] = oriY; o[2] = oriZ;
        
                
	this->d.setNull();
	this->o.normalize();
	this->r = this->o;
}

// Rotations
void Camera::rotate(GLdouble alpha, GLdouble beta)
{
        if (fabs(o[2]) > 0.8 &&
			((signbit(beta) == 0 && signbit(o[2]) == 0) ||
			 (signbit(beta) != 0 && signbit(o[2]) != 0)))
                beta = 0;
        else
                beta *= ANGLE_PER_ROTATION;
        alpha *= ANGLE_PER_ROTATION;
        
        if (alpha == 0 || beta == 0) {
                if (alpha != 0) {
                        r[0] = r[0] * cos(alpha)
                             - r[1] * sin(alpha);
                        r[1] = r[0] * sin(alpha)
                             + r[1] * cos(alpha);
                        r[2] = r[2] * cos(beta);
                } else if (beta != 0){
                        s[0] = r[0];
                        s[1] = r[1];
                        s[2] =    0;
			this->s.normalize();
                        
                        r[0] = r[0]                        * cos(beta)
                             - r[2] * s[0]                 * sin(beta);
                        
                        r[1] = r[1]                        * cos(beta)
                             - r[2] * s[1]                 * sin(beta);
                        
                        r[2] = r[2]                        * cos(beta)
                             + sqrt(r[0]*r[0] + r[1]*r[1]) * sin(beta);
                }
        } else {
                s[0] = r[0];
                s[1] = r[1];
                s[2] =    0;
		this->s.normalize();
                
                r[0] = r[0]        * cos(alpha) * cos(beta)
                     - r[1]        * sin(alpha) * cos(beta)
                     - r[2] * s[0] * cos(alpha) * sin(beta)
                     + r[2] * s[1] * sin(alpha) * sin(beta);
                
                r[1] = r[0]        * sin(alpha) * cos(beta)
                     + r[1]        * cos(alpha) * cos(beta)
                     - r[2] * s[0] * sin(alpha) * sin(beta)
                     - r[2] * s[1] * cos(alpha) * sin(beta);
                
                r[2] = r[2]                        * cos(beta)
                     + sqrt(r[0]*r[0] + r[1]*r[1]) * sin(beta);
        }
	this->r.normalize();
}

void Camera::lookTo(GLdouble oriX, GLdouble oriY, GLdouble oriZ)
{
        r[0] = oriX;
        r[1] = oriY;
        r[2] = oriZ;
	r.normalize();
}

// Translations
void Camera::move(GLdouble movForward, GLdouble movSideward, GLdouble movUpward)
{
        d[0] += (movForward  * o[0]
              -  movSideward * o[1]) * DIS_M;
        d[1] += (movForward  * o[1]
              +  movSideward * o[0]) * DIS_M;
        d[2] += (movForward  * o[2]) * DIS_M;
}

void Camera::goTo(GLdouble posX, GLdouble posY, GLdouble posZ)
{
        d[0] = posX - p[0];
        d[1] = posY - p[1];
        d[2] = posZ - p[2];
}

// Setters
void Camera::setPositionX(GLdouble posX)
{
        p[0] = posX;
}
void Camera::setPositionY(GLdouble posY)
{
        p[1] = posY;
}
void Camera::setPositionZ(GLdouble posZ)
{
        p[2] = posZ;
}

void Camera::setOrientationX(GLdouble posX)
{
        o[0] = posX;
}
void Camera::setOrientationY(GLdouble posY)
{
        o[1] = posY;
}
void Camera::setOrientationZ(GLdouble posZ)
{
        o[2] = posZ;
}

// Getters
GLdouble Camera::getPositionX()
{
        return p[0];
}
GLdouble Camera::getPositionY()
{
        return p[1];
}
GLdouble Camera::getPositionZ()
{
        return p[2];
}

GLdouble Camera::getOrientationX()
{
        return o[0];
}
GLdouble Camera::getOrientationY()
{
        return o[1];
}
GLdouble Camera::getOrientationZ()
{
        return o[2];
}

GLdouble Camera::getDirectionX()
{
        return d[0];
}
GLdouble Camera::getDirectionY()
{
        return d[1];
}
GLdouble Camera::getDirectionZ()
{
        return d[2];
}

// Keys handling
void Camera::keyDown(std::set<int> &keysPressed)
{
        {
                if (keysPressed.count('i'))
                        move(1, 0, 0);
                if (keysPressed.count('j'))
                        move(0, 1, 0);
                if (keysPressed.count('k'))
                        move(-1, 0, 0);
                if (keysPressed.count('l'))
                        move(0, -1, 0);

                if (keysPressed.count('I'))
                        move(DIS_B, 0, 0);
                if (keysPressed.count('J'))
                        move(0, DIS_B, 0);
                if (keysPressed.count('K'))
                        move(-DIS_B, 0, 0);
                if (keysPressed.count('L'))
                        move(0, -DIS_B, 0);
        }
        {
                if (keysPressed.count('w'))
                        rotate(0, 1);
                if (keysPressed.count('a'))
                        rotate(1, 0);
                if (keysPressed.count('s'))
                        rotate(0, -1);
                if (keysPressed.count('d'))
                        rotate(-1, 0);
                
                if (keysPressed.count('W'))
                        rotate(0, 1);
                if (keysPressed.count('A'))
                        rotate(1, 0);
                if (keysPressed.count('S'))
                        rotate(0, -1);
                if (keysPressed.count('D'))
                        rotate(-1, 0);
        }
        {
                if (keysPressed.count('o')) {
                        goTo(POS_X, POS_Y, POS_Z);
                        lookTo(ORI_X, ORI_Y, ORI_Z);
			keysPressed.erase('o');
                }
        }
}

// Calculate next position
void Camera::physic(double &physicDelta)
{
	this->s = d;
	this->s *= physicDelta * DIS_P;
	this->p += s;
	this->d -= this->s;
        
	this->s = this->r - this->o;
	this->s *= physicDelta * ANG_P;
	this->o += s;
	this->o.normalize();
}

// Place itself
void Camera::look()
{
        gluLookAt(p[0], p[1], p[2],
                  p[0] + o[0], p[1] + o[1], p[2] + o[2],
                  0, 0, 1);
}

// Destructor
Camera::~Camera()
{}
