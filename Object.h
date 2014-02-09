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

class Object
{

protected:

	// add vector parts, which are the other "objects" loaded in a obj file
	Texture texture;
	Shader shader;
	GLuint UniformShadowMapId, depthTextureId;

	std::set<Object> objects;

	std::set<std::tuple<Mesh,Texture,Shader>> meshs;

public:

	// TODO add vector<shader>, vector<texture>, vector<mesh>

	Object();
	Object(Mesh mesh, Texture texture, Shader shader);

	bool operator<(const Object &b) const;

	void addObject(Object& object);
	void delObject(Object& object);

	void draw();
	
	~Object();
};
