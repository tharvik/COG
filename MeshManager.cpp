#include "MeshManager.h"

#include <limits>
#include <vector>

#include "Logger.h"

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
	std::vector<std::array<std::array<unsigned short, 2>, 3>> f;

	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	while(file) {

		// get next word
		std::string word;
		getline(file, word, ' ');

		if (word == "o") {
			name = word;

		} else if (word == "v") {
			v.push_back(parseV<3>());

		} else if (word == "vt") {
			vt.push_back(parseV<2>());

		} else if (word == "f") {
			f.push_back(parseF());
		}

		if (word[0] == '#')
			cleanLine(word, false);
		else
			cleanLine(word, true);
	}

	file.close();
	logger::info("Parsing done for \"" + path + '\'', FL);

	this->map[path] = Mesh(name, v, vt, f);
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

std::array<std::array<unsigned short, 2>, 3>
	MeshManager::parseF()
{
	std::array<std::array<unsigned short, 2>, 3> array;
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
