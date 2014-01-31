#include "Object.h"

#include <iostream>
#include "Image.cpp"

Object::Object() : image("")
{}

void Object::setName(const std::string& name)
{
	this->name = name;
}

void Object::setImage(const Image<GLubyte>& image)
{
	this->image = image;
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
	this->image;
	this->image.bindTexture();

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
}


