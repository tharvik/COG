#include "Univers.h"

static Univers* local;

static void cleanup()
{
	local->~Univers();
}

// Constructors
Univers::Univers() : camera(), mainLight(5.98, -26.12, 15.39, 0.32, 0.76, -0.57)
{
	local = this;
	atexit(cleanup);
}

Univers::Univers(const GLdouble posX, const GLdouble posY, const GLdouble posZ,
			const GLdouble anglePhi, const GLdouble angleTeta,
			const GLdouble anglepsi) :
	camera(posX, posY, posZ, anglePhi, angleTeta, anglepsi)
{}

size_t Univers::addObject(const std::string &name)
{
	objects.push_back(loader.load(name));
        return objects.size() - 1;
}
size_t Univers::addObject(const std::string &&name)
{
	objects.push_back(loader.load(name));
        return objects.size() - 1;
}

size_t Univers::addObject(const Object &object)
{
        objects.push_back(object);
        return objects.size() - 1;
}
size_t Univers::addObject(const Object &object, const Texture &texture)
{
        objects.push_back(object);
        return objects.size() - 1;
}

size_t Univers::addSphere(const Sphere &theSphere)
{
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
void Univers::keyboard(std::set<int>& keysPressed)
{
        camera.keyDown(keysPressed);
}

void Univers::physic(double& physicDelta)
{
        camera.physic(physicDelta);
        //sphere.physic(physicDelta);
}

void Univers::draw() const
{
	for (auto& object: objects) {
                object.draw();
        }
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

// Destructor
Univers::~Univers()
{}
