#include "ObjLoader.h"

#include <vector>
#include <limits>

ObjLoader::ObjLoader() : lineCount(0) {}

std::vector<Object> ObjLoader::load(const std::string& path)
{
	this->path = path;
	file.open(path);

	std::vector<Object> objects;
	Object current;

	if (!file)
		logger::error("Unable to open \"" + path + '\'', FL);

	while(file) {

		std::string word = getNextWord();

		if (word == "o") {
			objects.push_back(current);

			current = Object();
			file >> word;
			current.setName(word);

		} else if (word == "v") {
			current.pushBackV(parseV());

		} else if (word == "vt") {
			current.pushBackVt(parseVt());

		} else if (word == "f") {
			current.pushBackF(parseF());

		}

		if (word[0] == '#')
			cleanLine(word, false);
		else
			cleanLine(word);
	}

	file.close();
	logger::info("Parsing done for \"" + path + '\'', FL);

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

		if(file.peek() != '/') {
			array[i][1] = 0;
		} else {
			file.get();
			file >> array[i][1];
		}
	}

	return array;
}

void ObjLoader::cleanLine(std::string word, bool logRemain)
{
	lineCount++;

	std::string tmp;
	getline(file, tmp);
	if(tmp.size() != 0 && logRemain)
		logger::warn("Discarding remaining results: \"" + word + " " +
				tmp + "\"", path, lineCount);
}
