#include "Mesh.h"

// Constructors
Mesh::Mesh()
{}

Mesh::Mesh(std::string name,
		std::vector<std::array<float, 3>> v,
		std::vector<std::array<float, 2>> vt,
		std::vector<std::array<std::array<unsigned short, 2>, 3>>
		f) : name(name), vt(vt), f(f)
{
	for(auto i : f)
		for(auto j : i)
			this->indices.push_back(j[0] - 1);

	this->buffers[0] = this->buffers[1] = 0;

	glGenBuffers(2, this->buffers.data());

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Copy the index data to the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool Mesh::operator<(const Mesh &b) const
{
	return this->name < b.name;
}

void Mesh::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glVertexPointer(3, GL_FLOAT, sizeof(this->v[0]), 0);

	// Bind the indices's VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_SHORT, 0);

	// Unbind buffers so client-side vertex arrays still work.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Disable the client side arrays again.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// Destructor
Mesh::~Mesh()
{}
