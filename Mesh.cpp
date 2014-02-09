#include "Mesh.h"

#include "opengl.h"

Mesh::Mesh() {}

Mesh::Mesh(std::string name,
	std::vector<std::array<float, 3>> v,
	std::vector<std::array<float, 2>> vt,
	std::vector<std::array<std::array<unsigned short, 2>, 3>>
	f) : name(name), v(v), vt(vt), f(f)
{}

bool Mesh::operator<(const Mesh &b) const
{
	return this->name < b.name;
}

void Mesh::draw()
{
	glBegin(GL_TRIANGLES);

	for(auto face : f) {
		for(auto vertex: face) {

			unsigned short pos = vertex[0] - 1;
			unsigned short tex = vertex[1] - 1;


			if(tex + 1 != 0)
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
