#include "Object.h"

// Constructors
Object::Object() : texture()
{
	this->shader = Shader("Resources/shaders/shadow.vShader", "Resources/shaders/shadow.pShader");
	this->UniformShadowMapId = glGetUniformLocation(this->shader.getShaderId(), "shadowMap");
}

Object::Object(Mesh mesh, Texture texture, Shader shader)
{
	this->meshs.push_back(std::make_tuple(mesh, texture, shader));
}

void Object::draw()
{
	for(auto t : this->meshs) {
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