#include "Univers.h"

using namespace std;

static Univers* local;

static void cleanup()
{
	local->~Univers();
}

Univers::Univers() : objects(), camera(), mainLight(5.98f, -26.12f, 15.39f,
				 0.32f, 0.76f, -0.57f)
{
	local = this;
	atexit(cleanup);
}

Univers::Univers(const GLdouble posX, const GLdouble posY, const GLdouble posZ,
			const GLdouble anglePhi, const GLdouble angleTeta,
			const GLdouble anglepsi) :
	objects(), camera(posX, posY, posZ, anglePhi, angleTeta, anglepsi),
	mainLight(5.98f, -26.12f, 15.39f, 0.32f, 0.76f, -0.57f)
{}

size_t Univers::addPlanet(const string& name)
{
        objects.insert(unique_ptr<Object>(new Planet(name)));
        return objects.size() - 1;
}

size_t Univers::addPlanet(const string& name, const Vvector pos)
{
        objects.insert(unique_ptr<Object>(new Planet(name, pos)));
        return objects.size() - 1;
}

void Univers::printInfo() const
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
	for (auto& object: objects)
                object->draw();
}

void Univers::refresh(universRefreshFlags flags)
{
	if (flags & LEVEL)
		for (auto& object: objects)
			object->calculateLevel(this->camera.getPosition());

        glLoadIdentity();
        
        // Shadows(&univers)
        perspective();
        camera.look();
        draw();
	glFinish();
        glutSwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutShowWindow();
}
