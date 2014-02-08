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
#include "ObjLoader.h"
#include "Sphere.h"

#define perspective() gluPerspective(FOV,(GLdouble)glutGet(GLUT_WINDOW_WIDTH)/\
                                     glutGet(GLUT_WINDOW_HEIGHT),NEAREST,FAREST)

class Univers {
private:
        
        //vector<> cameras;
        std::vector<Object> objects;
        ObjLoader loader;
        Camera camera;
        
        Sphere sphere; // Remove ?
        
        // Tick
        void draw();
public:
        // Constructors
        Univers();
	Univers(GLdouble posX, GLdouble posY, GLdouble posZ, GLdouble anglePhi,
                GLdouble angleTeta, GLdouble anglepsi);
        
        // Modifiers
        size_t addObject(std::string &objectPath); // Not tested
        size_t addObject(std::string &objectPath, std::string &texturePath); // Not tested
        size_t addObject(std::string &&objectPath); // Not tested
        size_t addObject(std::string &&objectPath, std::string &&texturePath);
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