#pragma once

#include <string>
#include <array>
#include <fstream>

#include "Object.h"

class ObjLoader
{
	public:
		template<typename T>
		static std::vector<Object<T>> load(std::string path);

	private:
		static std::array<float, 3> parseV(std::ifstream& file);
		static std::array<float, 2> parseVt(std::ifstream& file);
		static std::array<std::array<unsigned short, 2>, 3>
			parseF(std::ifstream& file);

		static std::string getNextWord(std::ifstream& file);
		static void cleanLine(std::ifstream& file);
};
