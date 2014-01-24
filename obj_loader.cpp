#include "obj_loader.h"

#include "logger.h"

#include <vector>
#include <limits>

#include <iostream>

std::vector<object> obj_loader::load(std::string path)
{
	std::ifstream file(path);

	std::vector<object> objects;
	object current;

	if(!file)
		log(ERROR, "Unable to open " + path, __FILE__, __LINE__);

	while(file) {

		std::string word = get_next_word(file);

		if(word == "o") {
			objects.push_back(current);

			current = object();
			file >> word;
			current.set_name(word);

		} else if(word == "v") {
			current.push_back_v(parse_v(file));

		} else if(word == "vt") {
			current.push_back_vt(parse_vt(file));

		} else if(word == "f") {
			current.push_back_f(parse_f(file));

		} else {
			if(word[0] != '#' && !word.empty())
				log(WARNING, "Dropping result on unhandled \"" +
						word + "\" keyword",
						__FILE__, __LINE__);
		}

		clean_line(file);
	}

	objects.erase(objects.begin());
	objects.push_back(current);
	return objects;
}

std::string obj_loader::get_next_word(std::ifstream& file)
{
	std::string word;
	getline(file, word, ' ');

	return word;
}

std::array<float, 3> obj_loader::parse_v(std::ifstream& file)
{
	std::array<float, 3> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<float, 2> obj_loader::parse_vt(std::ifstream& file)
{
	std::array<float, 2> array;
	for(unsigned short i = 0; i < array.size(); i++)
		file >> array[i];

	return array;
}

std::array<std::array<unsigned short, 2>, 3> obj_loader::parse_f(
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

void obj_loader::clean_line(std::ifstream& file)
{
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
