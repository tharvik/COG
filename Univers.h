#pragma once

#include <iostream>
#include "opengl.h"
#include <set>
#include <string>
#include <vector>

#include "Camera.h"
#include "config.h"
#include "Light.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Sphere.h"
#include "Texture.h"

#define perspective() gluPerspective(FOV,(GLdouble)glutGet(GLUT_WINDOW_WIDTH)/\
                                     glutGet(GLUT_WINDOW_HEIGHT),NEAREST,FAREST)

class Univers {
private:
        //vector<> cameras;
        std::vector<Object> objects;
        ObjectManager loader;
        Camera camera;
        Light mainLight;
        
        //Sphere sphere; // Remove ?
        
        // Tick
        void draw() const;
public:
        // Constructors
        Univers();
        Univers(const GLdouble posX, const GLdouble posY, const GLdouble posZ,
			const GLdouble anglePhi, const GLdouble angleTeta,
			const GLdouble anglepsi);
        
        // Modifiers
        size_t addObject(const std::string &name); // Not tested
        size_t addObject(const Object &object); // Not tested
        size_t addObject(const Object &object, const Texture &texture); // Not tested
        
        size_t addSphere(const Sphere &theSphere); // To remove!
        
        // Informations
        void printInfo();
        
        // Ticks handling
        void keyboard(std::set<int> &keysPressed);
        void refresh();
        void physic(double& physicDelta);
        
        // Destructor
        ~Univers();
};
