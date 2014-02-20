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
        
        void movX(const int x);
        void movY(const int y);
        void movZ(const int z);
        
        void enableGravity();
        
        void physic(const double &physicDelta);
        void draw() const;
        
        // Destructor
        ~Sphere();
};
