#include "ObjLoader.h"

#include "Logger.h"

#include <vector>
#include <limits>

template<typename T>
std::vector<Object<T>> ObjLoader::load(std::string path)
{
	std::ifstream file(path);

	std::vector<Object<T>> objects;
	Object<T> current;

	if(!file)
		log.error("Unable to open \"" + path + "\"");

	log.info("file \"" + path + "\" openned");

	while(file) {

		std::string word = getNextWord(file);

		if(word == "o") {
			objects.push_back(current);

			current = Object<T>();
			file >> word;
			current.set_name(word);

		} else if(word == "v") {
			current.pushBackV(parseV(file));

		} else if(word == "vt") {
			current.pushBackVt(parseVt(file));

		} else if(word == "f") {
			current.pushBackF(parseF(file));

		} else {
			if(word[0] != '#' && !word.empty())
				log.warn("Dropping result on unhandled \"" +
						word + "\" keyword");
		}

		cleanLine(file);
	}

	objects.erase(objects.begin());
	objects.push_back(current);
	return objects;
}

std::string ObjLoader::getNextWord(std::ifstream& file)
{
	std::string word;
	getline(file, word, ' ');

	return word;
}

std::array<float, 3> ObjLoader::parseV(std::ifstream& file)
{
	std::array<float, 3> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<float, 2> ObjLoader::parseVt(std::ifstream& file)
{
	std::array<float, 2> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<std::array<unsigned short, 2>, 3> ObjLoader::parseF(
		std::ifstream& file)
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

void ObjLoader::cleanLine(std::ifstream& file)
{
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
