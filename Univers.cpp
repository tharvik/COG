#include "Univers.h"



Univers::Univers() : camera()
{
	this->mainLight = Light(5.98, -26.12, 15.39, 0.32, 0.76, -0.57);			//
}

Univers::Univers(GLdouble posX, GLdouble posY, GLdouble posZ, GLdouble anglePhi,
                 GLdouble angleTeta, GLdouble anglepsi) : camera(posX, posY,
                 posZ, anglePhi, angleTeta, anglepsi)
{}

size_t Univers::addObject(std::string &objectPath)
{
        objects.push_back(loader.load(objectPath)[0]);
        return objects.size() - 1;
}
size_t Univers::addObject(std::string &&objectPath)
{
        objects.push_back(loader.load(objectPath)[0]);
        return objects.size() - 1;
}

size_t Univers::addObject(std::string &objectPath, std::string &texturePath)
{
        objects.push_back(loader.load(objectPath)[0]);
        objects[objects.size() - 1].setTexture(textures.load(texturePath));
        return objects.size() - 1;
}
size_t Univers::addObject(std::string &&objectPath, std::string &&texturePath)
{
        objects.push_back(loader.load(objectPath)[0]);
        objects[objects.size() - 1].setTexture(textures.load(texturePath));
        return objects.size() - 1;
}

size_t Univers::addObject(Object &object)
{
        objects.push_back(object);
        return objects.size() - 1;
}
size_t Univers::addObject(Object &object, Texture &texture)
{
        objects.push_back(object);
        return objects.size() - 1;
}

size_t Univers::addSphere(Sphere &theSphere)
{
        sphere = theSphere;
        return objects.size() - 1;
}

// Informations
void Univers::printInfo()
{
        std::cout << "CAMERA:" << std::endl
        << "\tPOSITION:    ["
        << camera.getPositionX() << "; "
        << camera.getPositionY() << "; "
        << camera.getPositionZ() << ']'
        << std::endl
        << "\tORIENTATION: ["
        << camera.getOrientationX() << "; "
        << camera.getOrientationY() << "; "
        << camera.getOrientationZ() << ']'
        << std::endl
        << std::endl;
}

// Tick
void Univers::keyboard(std::map<int, bool>& keysPressed)
{
        camera.keyDown(keysPressed);
}

void Univers::physic(double& physicDelta)
{
        camera.physic(physicDelta);
        //sphere.physic(physicDelta);
}

void Univers::draw()
{
	for (Object object: objects) {
                object.draw();
        }
        sphere.draw();
}

void Univers::refresh()
{
        glLoadIdentity();
        
        // Shadows(&univers)
        
        perspective();
        camera.look();
        draw();
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutShowWindow();
}
