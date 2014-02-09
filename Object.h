#pragma once

#include <array>
#include <string>
#include <vector>
#include <set>

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

	std::set<Object> objects;

public:

	// TODO add vector<shader>, vector<texture>, vector<mesh>

	Object();
	Object( const std::string name,
		const std::vector<std::array<float, 3>> v,
		const std::vector<std::array<float, 2>> vt,
		const std::vector<std::array<std::array<unsigned short, 2>, 3>>
			f);

	// TODO remove name? remove every modifier?
	void setName(const std::string& name);
	void setTexture(const Texture&  texture);
	void setTexture(const Texture&& texture);
	
	void pushBackV(const std::array<float, 3>& v);
	void pushBackVt(const std::array<float, 2>& vt);
	void pushBackF(const std::array<std::array<unsigned short, 2>, 3>& f);

	bool operator<(const Object &b) const;

	void addObject(Object& object);
	void delObject(Object& object);

	void draw();
	
	~Object();
};
