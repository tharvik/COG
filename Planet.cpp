#include "Planet.h"

Planet::Planet(const std::string& name) : Object(name)
{}

Planet::Planet(const std::string& name, Vvector pos) : Object(name, pos)
{}

void Planet::draw() const
{
        Object::draw();
}
