#include "Mesh.h"

// Constructors
Mesh::Mesh()
{}

Mesh::Mesh(std::vector<std::array<float, 3>> v,
		std::vector<std::array<float, 2>> vt,
		std::vector<unsigned short> indices)
		: sizeIndices(indices.size())
{
	std::vector<MeshVertice> pts;

	auto j = vt.begin();
	for(auto i = v.begin(); i != v.end() && j != vt.end(); i++, j++) {
		
#ifdef __APPLE__
		MeshVertice a = {*i, *j};
		pts.push_back(a);
#else
		pts.push_back( { *i, *j } );
#endif
	}

	glGenBuffers(3, this->buffers.data());

	// copy vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pts[0]) * pts.size(), pts.data(), GL_STATIC_DRAW);

	// copy indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[0]);
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
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// setup vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[1]);
	glVertexPointer(3, GL_FLOAT, sizeof(MeshVertice), 0);
	glTexCoordPointer(2, GL_FLOAT, sizeof(MeshVertice), (char*) NULL + offsetof(MeshVertice,vt));

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
{}
