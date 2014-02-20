#include "Sphere.h"

#include <math.h>

// Constructor
Sphere::Sphere() 
{
        p[0] = 0; p[1] = 0; p[2] = 4;
        v[0] = 0; v[1] = 0; v[2] = 0;
        a[0] = 0; a[1] = 0; a[2] = 0;
        
        m = 2;
        gravity = false;
}

void Sphere::movX(const int x)
{
        v[0] += x * 0.1;
}
void Sphere::movY(const int y)
{
        v[1] -= y * 0.1;
}
void Sphere::movZ(const int z)
{
        v[2] += z * 0.1;
}

void Sphere::enableGravity()
{
        gravity = true;
}

void Sphere::physic(const double &physicDelta)
{
        a[0] = 0; a[1] = 0; a[2] = 0;
        
        if (gravity && fabs(p[2]) > 0.01) {
                if (p[2] <= 0 && fabs(v[2]) < 0.008) {
                        v[2] = 0;
                }
                else if (p[2] <= 0) {// Reaction
                        a[2] += fabs(p[2]) / m;
                        v[2] /= 1.2;
                } else {
                        a[2] += -0.02; // Gravity
                }
        }
        
        if (fabs(v[0]) > 0.001)
                a[0] += -0.05 * v[0] / m;
        else
                v[0] = 0;
        if (fabs(v[1]) > 0.001)
                a[1] += -0.05 * v[1] / m;
        else
                v[1] = 0;
        if (fabs(v[2]) > 0.001)
                a[2] += -0.05 * v[2] / m;
        else
                v[2] = 0;
        
        v[0] += a[0];
        v[1] += a[1];
        v[2] += a[2];
        
        p[0] += v[0];
        p[1] += v[1];
        p[2] += v[2];
}

void Sphere::draw() const
{
        glTranslated(p[0], p[1], p[2]);
        glutSolidSphere(1, 20, 20);
}

// Destructor
Sphere::~Sphere()
{}
