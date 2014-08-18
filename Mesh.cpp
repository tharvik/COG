#include "Mesh.h"
#include "Logger.h"

using namespace std;

// Constructors


Mesh::Mesh() :
	radius(0), sizeIndices(), buffers()
{
	for (uint8_t i = 0; i < this->buffers.size(); i++)
	{
		sizeIndices[i] = 0;
		for(auto& buffer : this->buffers[i])
			buffer = 0;
	}
}

Mesh::Mesh(Mesh&& m) : radius(m.radius), sizeIndices(move(m.sizeIndices)),
buffers(move(m.buffers))
{
	for(uint8_t i = 0; i < m.buffers.size(); i++)
	{
		sizeIndices[i] = 0;
		for(auto& a : m.buffers[i])
			a = 0;
	}
}

Mesh::Mesh(const std::string& filePath) :
	radius(0), sizeIndices(), buffers()
{
	// open file
	ifstream file;
	file.open(filePath, ifstream::binary);
	if (!file.good())
		logger_error("Unable to open mesh file '" + filePath + "'");

	// load radius
	file.read(reinterpret_cast<char*>(&this->radius),
		  (sizeof(this->radius) / sizeof(char)));
	
	// load number of levels
	uint8_t nLevels;
	file.read(reinterpret_cast<char*>(&nLevels),
		  sizeof(nLevels) / sizeof(char));

	uint8_t i;
	for (i = 0; i < this->buffers.size(); i++)
	{
		if (i < nLevels) {
			// create buffers
			glGenBuffers(4, this->buffers[i].data());
			
			// get vertices
			fillBuffer<float>(this->buffers[i][0], file);
			fillBuffer<float>(this->buffers[i][1], file);
			fillBuffer<float>(this->buffers[i][2], file);
			this->sizeIndices[i] = fillBuffer<unsigned int>(
						     this->buffers[i][3], file);
		} else {
			this->buffers[i][0] = this->buffers[nLevels - 1][0];
			this->buffers[i][1] = this->buffers[nLevels - 1][1];
			this->buffers[i][2] = this->buffers[nLevels - 1][2];
			this->buffers[i][3] = this->buffers[nLevels - 1][3];
		}
	}
	
	// cleanup
	file.close();
	
	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	logger_info("Mesh loaded from '" + filePath + "'");
}

Mesh::Mesh(const std::array<std::vector<std::array<float, 3>>, 5>& v,
	   const std::array<std::vector<std::array<float, 2>>, 5>& vt,
	   const std::array<std::vector<unsigned int>, 5>& indices,
	   const float rad) :
	radius(rad), sizeIndices(), buffers()
{
	// load size indices
	for (uint8_t i = 0; i < this->buffers.size(); i++)
		this->sizeIndices[i] = (unsigned int) indices[i].size();

	// create and fill buffers
	for (uint8_t i = 0; i < this->buffers.size(); i++)
	{
		// create buffers
		glGenBuffers(GLint(this->buffers[i].size()),
			     buffers[i].data());
		
		// copy vertices
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[i][0]);
		glBufferData(GL_ARRAY_BUFFER,
			     long(sizeof(v[i][0]) * v[i].size()),
			     v[i].data(), GL_STATIC_DRAW);
		
		// copy vertices texture
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers[i][1]);
		glBufferData(GL_ARRAY_BUFFER,
			     long(sizeof(vt[i][0]) * vt[i].size()),
			     vt[i].data(), GL_STATIC_DRAW);
		
		// copy indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[i][3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			     long(sizeof(indices[i][0]) * indices[i].size()),
			     indices[i].data(), GL_STATIC_DRAW);
	}
	
	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool Mesh::operator<(const Mesh &m) const
{
	unsigned int a = 0, b = 0;

	for(auto i : this->buffers[0])
		a += i;

	for(auto i : m.buffers[0])
		b += i;

	return a < b;
}

float Mesh::getRadius()
{
	return this->radius;
}

void Mesh::draw(const uint8_t level) const
{
	// setup vertices
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[level][0]);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[level][1]);
	glTexCoordPointer(2, GL_FLOAT, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[level][2]);
	glNormalPointer(GL_FLOAT, 0, nullptr);

	// draw elements
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[level][3]);
	
	glDrawElements(GL_TRIANGLES,
		       int(this->sizeIndices[level]),
		       GL_UNSIGNED_INT, nullptr);

	// unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
	for (auto& level : this->buffers)
		glDeleteBuffers(GLsizei(level.size()), level.data());
}

template<typename T>
unsigned int Mesh::fillBuffer(GLuint buffer, std::ifstream& file)
{
	// read block size
	unsigned int size;
	file.read(reinterpret_cast<char*>(&size),
			sizeof(unsigned int) / sizeof(char));

	// get openGL buffer pointer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(size * sizeof(T)), nullptr,
		     GL_STATIC_DRAW);
	T* vertices = reinterpret_cast<T*>(
				glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	// check
	if(vertices == nullptr)
		logger_error("Failed to allocate graphic memory");

	// fill buffer
	file.read(reinterpret_cast<char*>(vertices),
			GLsizeiptr(size * sizeof(T) / sizeof(char)));

	// unmap openGL buffer pointer
	if(!glUnmapBuffer(GL_ARRAY_BUFFER))
		logger_error("Failed to unmap buffer during .mesh loading");

	return size;
}
