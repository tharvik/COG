#pragma once

#include <math.h>
#include "opengl.h"

#include "Object.h"
#include "utilities.h"

class Sphere : public Object {
private:
        GLdouble p[3];
        GLdouble v[3];
        GLdouble a[3];
        
        GLdouble m;
        
        bool gravity;
        
public:
        Sphere();
        
        void movX(int x);
        void movY(int y);
        void movZ(int z);
        
        void enableGravity();
        
        void physic(double &physicDelta);
        void draw();
};