#include "Object.h"

#include <iostream>

Object::Object() : texture()
{
	this->shader = Shader("Resources/shaders/shadow.vShader", "Resources/shaders/shadow.pShader");
	this->UniformShadowMapId = glGetUniformLocation(this->shader.getShaderId(),
													 "shadowMap");
}

void Object::setName(const std::string& name)
{
	this->name = name;
}

void Object::setTexture(const Texture& texture)
{
	this->texture = texture;
}
void Object::setTexture(const Texture&& texture)
{
	this->texture = texture;
}

void Object::pushBackV(const std::array<float, 3>& v)
{
	this->v.push_back(v);
}

void Object::pushBackVt(const std::array<float, 2>& vt)
{
	this->vt.push_back(vt);
}

void Object::pushBackF(const std::array<std::array<unsigned short, 2>, 3>& f)
{
	this->f.push_back(f);
}

void Object::draw()
{
	this->texture.bindTexture();
	this->shader.use();

	glBegin(GL_TRIANGLES);

	for(auto face : f) {
		for(auto vertex: face) {

			unsigned short pos = vertex[0] - 1;
			unsigned short tex = vertex[1] - 1;

			if(tex != (unsigned short) -1)
			{
				glTexCoord2f(this->vt[tex][0],
						-this->vt[tex][1]);
			}

			glVertex3d(this->v[pos][0],
					this->v[pos][1],
					this->v[pos][2]);
		}
	}

	glEnd();

	for(Object o : this->objects)
		o.draw();
}

Object::~Object()
{
}

bool Object::operator<(const Object &b) const
{
	this->name < b.name;
}

void Object::addObject(Object& object)
{
	this->objects.insert(object);
}

void Object::delObject(Object& object)
{
	this->objects.erase(object);
}
