#include "Object.h"

#include <iostream>

Object::Object() : image("/Users/Vianney/Xcode/COG/Test files/test.png", PNG)
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
	//this->image.bindTexture();

	glGenTextures(1, &this->imageId);
	glBindTexture(GL_TEXTURE_2D, this->imageId);
	glTexImage2D (
			GL_TEXTURE_2D,
			0, 4,
			this->image.getWidth(),
			this->image.getHeight(),
			0,
			this->image.getFormat(),
			GL_UNSIGNED_BYTE,
			this->image.getPixels()
		     );

	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

	glBegin(GL_TRIANGLES);

	for(auto face : f) {
		for(auto vertex: face) {

			unsigned short pos = vertex[0] - 1;
			unsigned short tex = vertex[1] - 1;

			if(tex != (unsigned short) -1)
				glTexCoord2i(this->vt[tex][0],
						this->vt[tex][1]);

			glVertex3d(this->v[pos][0],
					this->v[pos][1],
					this->v[pos][2]);
		}
	}

	glEnd();
}


