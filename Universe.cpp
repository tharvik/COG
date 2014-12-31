#include "Universe.h"

#include <LinearMath/btVector3.h>

using namespace std;

Universe::Universe()
: objects(), mainLight(btVector3({5.98f, -26.12f, 15.39f}), btVector3({0.32f, 0.76f, -0.57f}))
{
        broadphase = new btDbvtBroadphase();
        
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        
        solver = new btSequentialImpulseConstraintSolver;
        
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase,
                                                solver, collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

size_t Universe::addPlanet(const std::string& name)
{
        objects.insert(unique_ptr<Object>(new Planet(name)));
        return objects.size() - 1;
}

size_t Universe::addPlanet(const std::string& name, const btVector3 pos)
{
//        objects.insert(unique_ptr<Object>(new Planet(name, pos)));
        return objects.size() - 1;
}

void Universe::addRigidBody(btRigidBody* rigidBody)
{
        dynamicsWorld->addRigidBody(rigidBody);
}

void Universe::removeRigidBody(btRigidBody* rigidBody)
{
        dynamicsWorld->removeRigidBody(rigidBody);
}

const std::set<std::unique_ptr<Object>>& Universe::getObjects()
{
        return objects;
}

// Event
void Universe::event(const unique_ptr<Event>& event)
{
}

void Universe::physics(const double& dt)
{
        dynamicsWorld->stepSimulation(dt, 10); // TODO Settings
}

void Universe::draw() const
{
	for (auto& object: objects)
                object->draw();
}

void Universe::calculateLevel(const Camera& camera)
{
//        for (auto& object: objects)
//                object->calculateLevel(this->camera.getPosition());
}

Universe::~Universe()
{
        delete dynamicsWorld;
        delete solver;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphase;
}