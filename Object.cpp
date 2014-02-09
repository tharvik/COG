#include "Object.h"

#include <iostream>

Object::Object() : texture()
{
	this->shader = Shader("Resources/shaders/shadow.vShader", "Resources/shaders/shadow.pShader");
	this->UniformShadowMapId = glGetUniformLocation(this->shader.getShaderId(),
													 "shadowMap");
}

Object::Object( const std::string name,
		const std::vector<std::array<float, 3>> v,
		const std::vector<std::array<float, 2>> vt,
		const std::vector<std::array<std::array<unsigned short, 2>, 3>>
			f) : name(name), v(v), vt(vt), f(f)
{
	this->shader = Shader("Resources/shaders/shadow.vShader", "Resources/shaders/shadow.pShader");
	this->UniformShadowMapId = glGetUniformLocation(this->shader.getShaderId(), "shadowMap");
}

Object::Object(Mesh mesh, Texture texture, Shader shader)
{
	this->meshs.insert(std::make_tuple(mesh, texture, shader));
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

Object::~Object()
{
}

bool Object::operator<(const Object &b) const
{
	return this->name < b.name;
}

void Object::addObject(Object& object)
{
	this->objects.insert(object);
}

void Object::delObject(Object& object)
{
	this->objects.erase(object);
}
