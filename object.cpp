#include "object.h"

#include <iostream>

void object::set_name(std::string name)
{
	this->name = name;
}

void object::push_back_v(std::array<float, 3> v)
{
	this->v.push_back(v);
}

void object::push_back_vt(std::array<float, 2> vt)
{
	this->vt.push_back(vt);
}

void object::push_back_f(std::array<std::array<unsigned short, 2>, 3> f)
{
	this->f.push_back(f);
}

void object::draw()
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


