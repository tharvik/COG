#include "Object.h"

// Constructors
Object::Object()
{
}

Object::Object(Mesh& mesh, Texture& texture, Shader& shader)
{
	this->meshs.push_back(std::make_tuple(mesh, texture, shader));
}

void Object::draw()
{
	for(std::tuple<Mesh,Texture,Shader>& t : this->meshs) {
		std::get<2>(t).use();
		std::get<1>(t).bindTexture();
		std::get<0>(t).draw();
	}

	for(Object o : this->objects)
		o.draw();
}

bool Object::operator<(const Object &b) const
{
	return this < &b;
}

void Object::addObject(Object& object)
{
	this->objects.insert(object);
}

void Object::delObject(Object& object)
{
	this->objects.erase(object);
}

// Destructor
Object::~Object()
{}
