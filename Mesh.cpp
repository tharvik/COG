#include "Mesh.h"

// Constructors
Mesh::Mesh() : sizeIndices(0)
{
	for(auto& a : this->buffers)
		a = 0;
}

Mesh::Mesh(const std::string& name) : sizeIndices(0)
{
        
}

Mesh::Mesh(Mesh&& mesh) : sizeIndices(mesh.sizeIndices), buffers(mesh.buffers)
{
	for(auto& a : mesh.buffers)
		a = 0;
}

Mesh::Mesh(const std::vector<std::array<float, 3>>& v,
		const std::vector<std::array<float, 2>>& vt,
		const std::vector<unsigned int>& indices)
		: sizeIndices((GLsizei) indices.size())
{
	glGenBuffers((GLsizei) this->buffers.size(), this->buffers.data());

	// copy vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v[0]) * v.size(), v.data(),
			GL_STATIC_DRAW);

	// copy vertices texture
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vt[0]) * vt.size(), vt.data(),
			GL_STATIC_DRAW);

	// copy indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(indices[0]) * indices.size(),
			indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(const std::array<GLuint,4>& buffers, const unsigned int sizeIndices)
: sizeIndices(sizeIndices), buffers(buffers)
{}

bool Mesh::operator<(const Mesh &m) const
{
	unsigned short x = 0, y = 0;

	for(auto i : this->buffers)
		x += i;

	for(auto i : m.buffers)
		y += i;

	return x < y;
}

void Mesh::draw() const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// setup vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[2]);
	glNormalPointer(GL_FLOAT, 0, 0);

	// draw elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[3]);
	glDrawElements(GL_TRIANGLES, this->sizeIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

Mesh::~Mesh()
{
	glDeleteBuffers((GLsizei) this->buffers.size(), this->buffers.data());
}
