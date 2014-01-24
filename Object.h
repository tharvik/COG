#pragma once

#include <array>
#include <vector>
#include <string>

#include "opengl.h"
#include "Image.h"

template<class T>
class Object
{
	public:
		void setName(std::string name);
		void setImage(Image<T> image);

		void pushBackV(std::array<float, 3> v);
		void pushBackVT(std::array<float, 2> vt);
		void pushBackF(std::array<std::array<unsigned short, 2>, 3> f);

		void draw();
	private:
		std::string name;

		std::vector<std::array<float, 3>> v;
		std::vector<std::array<float, 2>> vt;
		std::vector<std::array<std::array<unsigned short, 2>, 3>> f;
};
