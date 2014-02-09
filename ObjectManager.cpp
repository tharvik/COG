#include "ObjectManager.h"

#include "Logger.h"

Object& ObjectManager::load(const std::string name)
{
	const auto iter = this->map.find(name);

	if(iter == this->map.end()) {

		const std::string path = "Resources/Test files/";

		Texture& texture(textures.load(path + name + ".png"));
		Mesh& mesh(meshs.load(path + name + ".obj"));
		Shader shader("Resources/shaders/shadow.vShader", "Resources/shaders/shadow.pShader");

		this->map[path] = Object(mesh, texture, shader);
		return this->map[path];

	} else {
		return iter->second;
	}
}
