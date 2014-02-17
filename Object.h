#pragma once

#include <array>
#include <string>
#include <vector>
#include <set>
#include <tuple>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

class Object {
protected:
	std::set<Object> objects;

	std::vector<std::tuple<Mesh*,Texture*,Shader*>> meshs;
	unsigned short resolution;

public: // TODO add vector<shader>, vector<texture>, vector<mesh>
        // Constructors
	Object();
	Object(Mesh& mesh, Texture& texture, Shader& shader);

	bool operator<(const Object &b) const;

	void addObject(Object& object);
	void delObject(Object& object);

	void draw();
	
        // Destructor
	~Object();
};
