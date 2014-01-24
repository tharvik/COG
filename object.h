#pragma once

#include <array>
#include <vector>
#include <string>
#include <GL/glew.h>

class object
{
	public:
		void set_name(std::string name);
		void push_back_v(std::array<float, 3> v);
		void push_back_vt(std::array<float, 2> vt);
		void push_back_f(
				std::array<std::array<unsigned short, 2>, 3> f);

		void draw();
	private:
		std::string name;

		std::vector<std::array<float, 3>> v;
		std::vector<std::array<float, 2>> vt;
		std::vector<std::array<std::array<unsigned short, 2>, 3>> f;
};
