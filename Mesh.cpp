#include "Mesh.h"
#include "Logger.h"
#include <fstream>

using namespace std;

// Constructors
Mesh::Mesh() : sizeIndices(0)
{
	for(auto& a : this->buffers)
		a = 0;
}

template<typename T>
static unsigned int fillBuffer(GLuint& buffer, ifstream& file)
{
	unsigned int size;
	file.read(reinterpret_cast<char*>(&size),
			sizeof(unsigned int) / sizeof(char));

	// get buffer from OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), NULL,
		     GL_STATIC_DRAW);
	T* vertices = reinterpret_cast<T*>(
				glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
																	
	if(vertices == NULL)
		logger::error("Fail to allocate graphic memory", _FL_);

	file.read(reinterpret_cast<char*>(vertices),
			size * sizeof(T) / sizeof(char));

	if(!glUnmapBuffer(GL_ARRAY_BUFFER))
		logger::error("Fail to unmap buffer during .mesh loading", _FL_);

	return size;
}

Mesh::Mesh(const string& filePath) : sizeIndices(0)
{
	ifstream file;
	file.open(filePath, ifstream::binary);
	if (!file.good())
		logger::error("Unable to open mesh file \"" + filePath +
			      "\"", _FL_);

	// setup reading
	glGenBuffers((GLint) this->buffers.size(), buffers.data());

	// get vertices
	fillBuffer<float>(this->buffers[0], file);
	fillBuffer<float>(this->buffers[1], file);
	fillBuffer<float>(this->buffers[2], file);
	this->sizeIndices = fillBuffer<unsigned int>(this->buffers[3], file);

	// cleanup
	file.close();
	logger::info("Mesh loaded from '" + filePath + "'", _FL_);
}

Mesh::Mesh(Mesh&& mesh) : sizeIndices(mesh.sizeIndices), buffers(mesh.buffers)
{
	for(auto& a : mesh.buffers)
		a = 0;
}

Mesh::Mesh(const vector<array<float, 3>>& v,
	   const vector<array<float, 2>>& vt,
	   const vector<unsigned int>& indices)
: sizeIndices((unsigned int) indices.size())
{
	glGenBuffers((GLsizei) this->buffers.size(), this->buffers.data());

	// copy vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(GL_ARRAY_BUFFER,
		     (long) (sizeof(v[0]) * v.size()), v.data(),
		     GL_STATIC_DRAW);

	// copy vertices texture
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ARRAY_BUFFER,
		     (long) (sizeof(vt[0]) * vt.size()), vt.data(),
			GL_STATIC_DRAW);

	// copy indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		     (long) (sizeof(indices[0]) * indices.size()),
		     indices.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(const array<GLuint,4>& arrayBuffers, const unsigned int size)
: sizeIndices(size), buffers(arrayBuffers)
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
	glDrawElements(GL_TRIANGLES,
		       (int) this->sizeIndices,
		       GL_UNSIGNED_INT, 0);

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
