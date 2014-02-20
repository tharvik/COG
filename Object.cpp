#include "Object.h"

// Constructors
Object::Object() : resolution(0)
{}

Object::Object(Mesh& mesh, Texture& texture, Shader& shader) : resolution(0)
{
	auto tuple = std::make_tuple(&mesh, &texture, &shader);
	this->meshs.push_back(tuple);
}

void Object::draw() const
{
	std::get<2>(this->meshs[this->resolution])->use();
	std::get<1>(this->meshs[this->resolution])->bindTexture();
	std::get<0>(this->meshs[this->resolution])->draw();

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
