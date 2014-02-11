#pragma once

#include <math.h>
#include "opengl.h"

#include "Object.h"
#include "utilities.h"

class Sphere {
private:
	std::array<GLdouble,3> p;
	std::array<GLdouble,3> v;
	std::array<GLdouble,3> a;
        
        GLdouble m;
        
        bool gravity;
        
public:
        // Constructor
        Sphere();
        
        void movX(int x);
        void movY(int y);
        void movZ(int z);
        
        void enableGravity();
        
        void physic(double &physicDelta);
        void draw();
        
        // Destructor
        ~Sphere();
};
