#include "Object.h"

// Constructors
Object::Object()
{
}

Object::Object(Mesh& mesh, Texture& texture, Shader& shader)
{
	auto tuple = std::make_tuple(&mesh, &texture, &shader);
	this->meshs.push_back(tuple);
}

void Object::draw()
{
	for(auto t : this->meshs) {
		std::get<2>(t)->use();
		std::get<1>(t)->bindTexture();
		std::get<0>(t)->draw();
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
