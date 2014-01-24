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
		static std::array<float, 3> parse_v(std::ifstream& file);
		static std::array<float, 2> parse_vt(std::ifstream& file);
		static std::array<std::array<unsigned short, 2>, 3>
			parse_f(std::ifstream& file);

		static std::string get_next_word(std::ifstream& file);
		static void clean_line(std::ifstream& file);
};
