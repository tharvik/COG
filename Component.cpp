#include "Component.h"

Component::Component(const Object& object) : Object(object), position()
{}

Component::Component(const Object& object, const Vvector& position) :
	Object(object), position(position)
{}

void Component::draw() const
{
	glPushMatrix();
	glTranslatef(position.x(), position.y(), position.z());
	Object::draw();
	glPopMatrix();
}
