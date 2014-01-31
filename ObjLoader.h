#pragma once

#include <string>
#include <array>
#include <fstream>

#include "Object.h"
#include "Logger.h"
#include "opengl.h"

class ObjLoader
{
	public:
		ObjLoader();

		std::vector<Object> load(const std::string& path);

	private:
		std::array<float, 3> parseV();
		std::array<float, 2> parseVt();
		std::array<std::array<unsigned short, 2>, 3>
			parseF();

		std::string getNextWord();
		void cleanLine(std::string word, bool logRemain = true);

		// current load
		std::string path;
		std::ifstream file;
		unsigned short lineCount;
};
