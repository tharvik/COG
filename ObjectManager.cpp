#include "ObjectManager.h"

// Constructor
ObjectManager::ObjectManager()
{}

Object& ObjectManager::load(const std::string name)
{
	const auto iter = this->map.find(name);

	if(iter == this->map.end()) {

		const std::string path = "Resources/objects/" + name + "/" + name;

		Texture& texture(textures.load(path + ".png"));
		Mesh& mesh(meshs.load(path + ".obj"));
		Shader shader(shaders.load(path + ".vShader", path + ".pShader"));

		Object object = Object(mesh, texture, shader);
		this->map[path] = object;
		return this->map[path];

	} else {
		return iter->second;
	}
}

// Destructor
ObjectManager::~ObjectManager()
{}
