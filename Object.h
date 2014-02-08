#pragma once

#include <array>
#include <string>
#include <vector>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"

class Object
{

protected:

	// add vector parts, which are the other "objects" loaded in a obj file

	std::string name;
	Texture texture;
	Shader shader;
	GLuint UniformShadowMapId, depthTextureId;

	std::vector<std::array<float, 3>> v;
	std::vector<std::array<float, 2>> vt;
	std::vector<std::array<std::array<unsigned short, 2>, 3>> f;

public:

	Object();
	
	void setName(const std::string& name);
	void setTexture(const Texture&  texture);
	void setTexture(const Texture&& texture);
	
	void pushBackV(const std::array<float, 3>& v);
	void pushBackVt(const std::array<float, 2>& vt);
	void pushBackF(const std::array<std::array<unsigned short, 2>, 3>& f);
	
	void draw();
	
	~Object();
};
