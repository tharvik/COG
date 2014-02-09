#pragma once

#include <iostream>
#include <map>
#include "opengl.h"
#include <vector>
#include <string>

#include "Camera.h"
#include "config.h"
#include "Texture.h"
#include "Object.h"
#include "Sphere.h"
#include "Light.h"																//

#include "ObjectManager.h"

#define perspective() gluPerspective(FOV,(GLdouble)glutGet(GLUT_WINDOW_WIDTH)/\
                                     glutGet(GLUT_WINDOW_HEIGHT),NEAREST,FAREST)

class Univers {
private:
        
        //vector<> cameras;
        std::vector<Object> objects;
        ObjectManager loader;
        Camera camera;
        Light mainLight;														//
		
        Sphere sphere; // Remove ?

        // Tick
        void draw();
public:
        // Constructors
        Univers();
		Univers(GLdouble posX, GLdouble posY, GLdouble posZ, GLdouble anglePhi,
                GLdouble angleTeta, GLdouble anglepsi);
        
        // Modifiers
        size_t addObject(std::string &name); // Not tested
        size_t addObject(std::string &&name); // Not tested
        size_t addObject(Object &object); // Not tested
        size_t addObject(Object &object, Texture &texture); // Not tested
        
        size_t addSphere(Sphere &theSphere); // To remove!
        
        // Informations
        void printInfo();
        
        // Tick
        void keyboard(std::map<int, bool> &keysPressed);
        void refresh();
        void physic(double& physicDelta);
};
