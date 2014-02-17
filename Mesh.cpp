#include "Mesh.h"

// Constructors
Mesh::Mesh()
{
	for(auto& a : this->buffers)
		a = 0;
}

Mesh::Mesh(Mesh&& m)
{
	this->sizeIndices = m.sizeIndices;
	this->buffers = m.buffers;

	for(auto& a : m.buffers)
		a = 0;
}

Mesh::Mesh(std::vector<std::array<float, 3>> v,
		std::vector<std::array<float, 2>> vt,
		std::vector<unsigned short> indices)
		: sizeIndices(indices.size())
{
	glGenBuffers(this->buffers.size(), this->buffers.data());

	// copy vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data(),
			GL_STATIC_DRAW);

	// copy vertices texture
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vt[0]) * vt.size(), vt.data(),
			GL_STATIC_DRAW);

	// copy indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(indices[0]) * indices.size(),
			indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(std::array<GLuint,4> buffers, unsigned int sizeIndices)
: sizeIndices(sizeIndices), buffers(buffers)
{}

bool Mesh::operator<(const Mesh &b) const
{
	unsigned short x = 0, y = 0;

	for(auto i : this->buffers)
		x += i;

	for(auto i : b.buffers)
		y += i;

	return x < y;
}

void Mesh::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// setup vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	// draw elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[0]);
	glDrawElements(GL_TRIANGLES, this->sizeIndices, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

// Destructor
Mesh::~Mesh()
{
	glDeleteBuffers(this->buffers.size(), this->buffers.data());
}
