#pragma once

#include <string>
#include <map>

#include "Object.h"

class ObjectManager {

	public:
		Object& load(const std::string path);

	private:
		void parse();

		template<unsigned short size>
		std::array<float, size> parseV();
		std::array<std::array<unsigned short, 2>, 3> parseF();

		void cleanLine(const std::string word, const bool log);

		std::map<std::string,Object> map;

		// current loading
		std::string path;
		std::ifstream file;
		unsigned short lineCount;
};
