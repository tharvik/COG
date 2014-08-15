#include "Camera.h"

#include <math.h>

// Constructors
Camera::Camera()
{
        p[0] = INITIAL_POSITION_X;
	p[1] = INITIAL_POSITION_Y;
	p[2] = INITIAL_POSITION_Z;
        o[0] = INITIAL_ORIENTATION_X;
	o[1] = INITIAL_ORIENTATION_Y;
	o[2] = INITIAL_ORIENTATION_Z;

	this->d.setNull();
	this->o.normalize();
	this->r = this->o;
}

Camera::Camera(const GLdouble posX, const GLdouble posY, const GLdouble posZ,
               const GLdouble oriX, const GLdouble oriY, const GLdouble oriZ)
{
        if (!oriX && !oriY && !oriZ) {
                logger::warn("The orientation vector given to the camera was of\
                             length 0", _FL_);
        } else {
		p[0] = (float) posX; p[1] = (float) posY; p[2] = (float) posZ;
		o[0] = (float) oriX; o[1] = (float) oriY; o[2] = (float) oriZ;
	}

	this->d.setNull();
	this->o.normalize();
	this->r = this->o;
}

// Rotations
void Camera::rotate(const GLdouble alpha, const GLdouble beta)
{
	GLdouble a = alpha;
	GLdouble b = beta;
	Vvector s;

        if (fabs(o[2]) > 0.8 &&
			((signbit(beta) == 0 && signbit(o[2]) == 0) ||
			 (signbit(beta) != 0 && signbit(o[2]) != 0)))
                b = 0;
        else
                b *= ANGLE_PER_ROTATION;
        a *= ANGLE_PER_ROTATION;

        if (a == 0 || b == 0) {
                if (a != 0) {
                        r[0] = (float) (r[0] * cos(a)
                             - r[1] * sin(a));
                        r[1] = (float) (r[0] * sin(a)
                             + r[1] * cos(a));
                        r[2] = (float) (r[2] * cos(b));
                } else if (b != 0){
                        s[0] = r[0];
                        s[1] = r[1];
                        s[2] =    0;
			s.normalize();
                        
                        r[0] = (float) (r[0]                        * cos(b)
                             - r[2] * s[0]                 * sin(b));
                        
                        r[1] = (float) (r[1]                        * cos(b)
                             - r[2] * s[1]                 * sin(b));
                        
                        r[2] = (float) (r[2]                        * cos(b)
                             + sqrt(r[0]*r[0] + r[1]*r[1]) * sin(b));
                }
        } else {
                s[0] = r[0];
                s[1] = r[1];
                s[2] =    0;
		s.normalize();
                
                r[0] = (float) (r[0]        * cos(a) * cos(b)
                     - r[1]        * sin(a) * cos(b)
                     - r[2] * s[0] * cos(a) * sin(b)
                     + r[2] * s[1] * sin(a) * sin(b));
                
                r[1] = (float) (r[0]        * sin(a) * cos(b)
                     + r[1]        * cos(a) * cos(b)
                     - r[2] * s[0] * sin(a) * sin(b)
                     - r[2] * s[1] * cos(a) * sin(b));
                
                r[2] =  (float) (r[2]                        * cos(b)
                     + sqrt(r[0]*r[0] + r[1]*r[1]) * sin(b));
        }
	this->r.normalize();
}

void Camera::lookTo(const GLdouble oriX, const GLdouble oriY,
		const GLdouble oriZ)
{
        r[0] = (float) oriX;
        r[1] = (float) oriY;
        r[2] = (float) oriZ;
	r.normalize();
}

// Translations
void Camera::move(const GLdouble movForward, const GLdouble movSideward,
		const GLdouble movUpward)
{
        d[0] += (movForward  * o[0]
              -  movSideward * o[1]) * DISTANCE_PER_MOVE;
        d[1] += (movForward  * o[1]
              +  movSideward * o[0]) * DISTANCE_PER_MOVE;
        d[2] += (movForward  * o[2]) * DISTANCE_PER_MOVE;
}

void Camera::goTo(const GLdouble posX, const GLdouble posY, const GLdouble posZ)
{
        d[0] = (float) posX - p[0];
        d[1] = (float) posY - p[1];
        d[2] = (float) posZ - p[2];
}

// Setters
void Camera::setPositionX(const GLdouble posX)
{
        p[0] = (float) posX;
}
void Camera::setPositionY(const GLdouble posY)
{
        p[1] = (float) posY;
}
void Camera::setPositionZ(const GLdouble posZ)
{
        p[2] = (float) posZ;
}

void Camera::setOrientationX(const GLdouble posX)
{
        o[0] = (float) posX;
}
void Camera::setOrientationY(const GLdouble posY)
{
        o[1] = (float) posY;
}
void Camera::setOrientationZ(const GLdouble posZ)
{
        o[2] = (float) posZ;
}

// Getters
const Vvector& Camera::getPosition() const
{
	return this->p;
}

GLdouble Camera::getPositionX() const
{
        return p.x();
}
GLdouble Camera::getPositionY() const
{
        return p.y();
}
GLdouble Camera::getPositionZ() const
{
        return p.z();
}

GLdouble Camera::getOrientationX() const
{
        return o.x();
}
GLdouble Camera::getOrientationY() const
{
        return o.y();
}
GLdouble Camera::getOrientationZ() const
{
        return o.z();
}

GLdouble Camera::getDirectionX() const
{
        return d.x();
}
GLdouble Camera::getDirectionY() const
{
        return d.y();
}
GLdouble Camera::getDirectionZ() const
{
        return d.z();
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
                        move(DISTANCE_PER_MOVE, 0, 0);
                if (keysPressed.count('J'))
                        move(0, DISTANCE_PER_MOVE, 0);
                if (keysPressed.count('K'))
                        move(-DISTANCE_PER_MOVE, 0, 0);
                if (keysPressed.count('L'))
                        move(0, -DISTANCE_PER_MOVE, 0);
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
                        goTo(INITIAL_POSITION_X, INITIAL_POSITION_Y,
					INITIAL_POSITION_Z);
                        lookTo(INITIAL_ORIENTATION_X, INITIAL_ORIENTATION_Y,
					INITIAL_ORIENTATION_Z);
			keysPressed.erase('o');
                }
        }
}

// Calculate next position
void Camera::physic(const double &physicDelta)
{
	Vvector s;
	s = d;
	s *= (float) (physicDelta * DISTANCE_PER_PHYSIC);
	this->p += s;
	this->d -= s;

	s = this->r - this->o;
	s *= (float) (physicDelta * ANGLE_PER_PHYSIC);
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
