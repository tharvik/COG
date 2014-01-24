#include "ObjLoader.h"

#include <vector>
#include <limits>

ObjLoader::ObjLoader() : lineCount(0) {}

template<typename T>
std::vector<Object<T>> ObjLoader::load(const std::string& path)
{
	this->path = path;
	this->file.open(path);

	std::vector<Object<T>> objects;
	Object<T> current;

	if(!file)
		logger::error("Unable to open \"" + path + "\"", FL);

	while(file) {

		std::string word = getNextWord();

		if(word == "o") {
			objects.push_back(current);

			current = Object<T>();
			file >> word;
			current.set_name(word);

		} else if(word == "v") {
			current.pushBackV(parseV());

		} else if(word == "vt") {
			current.pushBackVt(parseVt());

		} else if(word == "f") {
			current.pushBackF(parseF());

		}
		cleanLine();
	}

	file.close();
	logger::info("Parsing done for \"" + path + "\"", FL);

	objects.erase(objects.begin());
	objects.push_back(current);
	return objects;
}

std::string ObjLoader::getNextWord()
{
	std::string word;
	getline(file, word, ' ');

	return word;
}

std::array<float, 3> ObjLoader::parseV()
{
	std::array<float, 3> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<float, 2> ObjLoader::parseVt()
{
	std::array<float, 2> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<std::array<unsigned short, 2>, 3> ObjLoader::parseF()
{
	std::array<std::array<unsigned short, 2>, 3> array;
	for(unsigned short i = 0; i < array.size(); i++) {

		file >> array[i][0];

		if(file.get() != '/') {
			array[i][1] = 0;
			continue;
		}

		file >> array[i][1];
	}

	return array;
}

void ObjLoader::cleanLine()
{
	lineCount++;

	std::string tmp;
	getline(file, tmp);
	if(tmp.size() != 0)
		logger::warn("Discarding remaining results", path, lineCount);
}
