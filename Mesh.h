#pragma once

#include <array>
#include "opengl.h"
#include <string>
#include <vector>

class Mesh {
	private:
		unsigned int sizeIndices;
		std::array<GLuint,3> buffers;

	public:
		// Constructors
		Mesh();
		Mesh(Mesh&& m);

		// v: verticle,
		// vt: verticle texture,
		// indices starting from 0
		Mesh(std::vector<std::array<float, 3>> v,
				std::vector<std::array<float, 2>> vt,
				std::vector<unsigned short> indices);

		void draw();

		bool operator<(const Mesh &b) const;

		// Destructor
		~Mesh();
};
