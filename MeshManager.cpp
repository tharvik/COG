#include "MeshManager.h"

#include "Logger.h"

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

Mesh& MeshManager::loadMesh(const std::string path)
{
	// test if already existing
	const auto iter = this->map.find(path);
	if(iter != this->map.end())
		return iter->second;

	this->file.open(path, std::ifstream::binary);
	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	// setup reading
	std::array<GLuint,4> buffers;
	glGenBuffers(buffers.size(), buffers.data());

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


Mesh& MeshManager::load(const std::string path)
{
	// test if already existing
	const auto iter = this->map.find(path);
	if(iter != this->map.end())
		return iter->second;

	// setup manager
	this->lineCount = 0;
	this->path = path;
	this->file.open(path);

	// current object
	std::string name;
	std::vector<std::array<float, 3>> v;
	std::vector<std::array<float, 2>> vt;
	std::vector<std::array<std::array<unsigned int, 2>, 3>> f;

	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	std::string word = "#";
	do {
		if (word == "o") {
			name = word;

		} else if (word == "v") {
			v.push_back(parseV<3>());

		} else if (word == "vt") {
			vt.push_back(parseV<2>());

		} else if (word == "f") {
			f.push_back(parseF());
		}

		if (word.size() == 0 || word[0] == '#')
			cleanLine(word, false);
		else
			cleanLine(word, true);

		// get next word
		getline(file, word, ' ');

	} while(file);

	file.close();
	logger::info("Parsing done for \"" + path + '\'', FL);

	std::vector<std::array<float, 2>> vt_reorder;
	
#ifdef __APPLE__
	std::array<float, 2> a = {0, 0};
	vt_reorder.insert(vt_reorder.begin(), v.size(), a);
#else
	vt_reorder.insert(vt_reorder.begin(), v.size(), {{ 0, 0 }} );
#endif

	
	// TODO remove indices temporary and directly parse it
	std::vector<unsigned int> indices;
	for(auto i : f) {
		for(auto j : i) {
			indices.push_back(j[0] - 1);
			vt_reorder[j[0] - 1] = vt[j[1] - 1];
		}
	}

	this->map.insert(std::make_pair(path, std::move(Mesh(v, vt_reorder, indices))));
	return this->map[path];
}

template<unsigned short size>
std::array<float, size> MeshManager::parseV()
{
	std::array<float, size> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<std::array<unsigned int, 2>, 3>
	MeshManager::parseF()
{
	std::array<std::array<unsigned int, 2>, 3> array;
	for(unsigned short i = 0; i < array.size(); i++) {

		file >> array[i][0];

		if(file.peek() != '/') {
			array[i][1] = 0;
		} else {
			file.get();
			file >> array[i][1];
		}
	}

	return array;
}

void MeshManager::cleanLine(const std::string word, const bool log)
{
	lineCount++;

	std::string tmp;
	getline(file, tmp);

	if(tmp.size() != 0 && log)
		logger::warn("Discarding remaining results: \"" + word + " " +
				tmp + "\"", path, lineCount);
}
