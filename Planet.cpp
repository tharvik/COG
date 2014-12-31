#include "Planet.h"

Planet::Planet(const std::string& name) : Object(name)
{}


void Planet::draw() const
{
        Object::draw();
}
