#include "Object.h"

#include <iostream>

template<class T>
void Object<T>::setName(std::string name)
{
	this->name = name;
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


