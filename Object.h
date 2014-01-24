#pragma once

#include <array>
#include <vector>
#include <string>

#include "opengl.h"
#include "Image.h"

class Object
{
	public:
		Object();

		void setName(const std::string& name);
		void setImage(const Image<GLubyte>& image);

		void pushBackV(const std::array<float, 3>& v);
		void pushBackVt(const std::array<float, 2>& vt);
		void pushBackF(const std::array<
				std::array<unsigned short, 2>, 3>& f);

		void draw();
	private:
		std::string name;
		Image<GLubyte> image;
		GLuint imageId;

		std::vector<std::array<float, 3>> v;
		std::vector<std::array<float, 2>> vt;
		std::vector<std::array<std::array<unsigned short, 2>, 3>> f;
};
