#include "MeshManager.h"

#include "Logger.h"

MeshManager::MeshManager()
{}

template<typename T>
static unsigned int fillBuffer(GLuint& buffer, std::ifstream& file)
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
		logger::error("Fail to allocate graphic memory", FL);

	file.read(reinterpret_cast<char*>(vertices),
			size * sizeof(T) / sizeof(char));

	if(!glUnmapBuffer(GL_ARRAY_BUFFER))
		logger::error("Fail to unmap buffer during .mesh loading", FL);

	return size;
}

Mesh& MeshManager::load(const std::string& path)
{
	// test if already existing
	const auto iter = this->map.find(path);
	if(iter != this->map.end())
		return iter->second;

	std::ifstream file;
	file.open(path, std::ifstream::binary);
	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	// setup reading
	std::array<GLuint,4> buffers;
	glGenBuffers((unsigned int) buffers.size(), buffers.data());

	// get vertices
	fillBuffer<float>(buffers[0], file);
	fillBuffer<float>(buffers[1], file);
	fillBuffer<float>(buffers[2], file);
	unsigned int size = fillBuffer<unsigned int>(buffers[3], file);

	// cleanup
	file.close();
	logger::info("Parsing done for \"" + path + '\'', FL);

	this->map.insert(std::make_pair(path, std::move(Mesh(buffers, size))));
	return this->map[path];
}
