#pragma once

#include <array>
#include "opengl.h"
#include <string>
#include <vector>

class Mesh {
private:
        std::string name;
        std::vector<std::array<float, 3>> v;
        std::vector<std::array<float, 2>> vt;
        std::vector<std::array<std::array<unsigned short, 2>, 3>> f;
        
	std::vector<std::array<float,3>> g_Vertices;

	std::vector<unsigned short> indices;

	std::array<GLuint,2> buffers;

public:
        // Constructors
        Mesh();
        Mesh(std::string name,
             std::vector<std::array<float, 3>> v,
             std::vector<std::array<float, 2>> vt,
             std::vector<std::array<std::array<unsigned short, 2>, 3>>
		     f);
        
        void draw();
        
        bool operator<(const Mesh &b) const;
        
        // Destructor
        ~Mesh();
};
