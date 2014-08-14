#include "Planet.h"

using namespace std;

Planet::Planet(const string& name) : Object(name)
{}

Planet::Planet(const std::string& name, Vvector pos) : Object(name, pos)
{}

void Planet::draw() const
{
        Object::draw();
}
