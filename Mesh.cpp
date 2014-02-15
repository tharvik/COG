#include "Mesh.h"

// Constructors
Mesh::Mesh()
{}

Mesh::Mesh(std::vector<std::array<float, 3>> v,
		std::vector<unsigned short> indices)
		: sizeIndices(indices.size())
{
	this->buffers[0] = this->buffers[1] = 0;

	glGenBuffers(2, this->buffers.data());

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool Mesh::operator<(const Mesh &b) const
{
	return (this->buffers[0] + this->buffers[1]) < (b.buffers[0] + b.buffers[1]);
}

void Mesh::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glVertexPointer(3, GL_FLOAT, sizeof(std::array<float,3>), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[1]);
	glDrawElements(GL_TRIANGLES, this->sizeIndices, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// Destructor
Mesh::~Mesh()
{}
