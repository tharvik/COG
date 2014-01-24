#include "Object.h"

#include <iostream>

template<class T>
void Object<T>::setName(std::string name)
{
	this->name = name;
}

template<class T>
void Object<T>::setImage(Image<T> image)
{
	this->image = image;
}

template<class T>
void Object<T>::pushBackV(std::array<float, 3> v)
{
	this->v.push_back(v);
}

template<class T>
void Object<T>::pushBackVt(std::array<float, 2> vt)
{
	this->vt.push_back(vt);
}

template<class T>
void Object<T>::pushBackF(std::array<std::array<unsigned short, 2>, 3> f)
{
	this->f.push_back(f);
}

template<class T>
void Object<T>::draw()
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
				glTexCoord2i(this->vt[tex][0], this->vt[tex][1]);

			glVertex3d(this->v[pos][0],
					this->v[pos][1],
					this->v[pos][2]);
		}
	}

	glEnd();
}


