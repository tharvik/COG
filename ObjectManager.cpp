#include "ObjectManager.h"

ObjectManager::ObjectManager() : path("Resources/objects/")
{}

ObjectManager::ObjectManager(std::string path) :
	path((path[path.size() - 1] == '/') ? path : path + '/')
{}

Object ObjectManager::load(const std::string name)
{
	const std::string path = this->path + name + "/" + name;
	Texture& texture(textures.load(path + ".png"));
	Mesh& mesh(meshs.load(path + ".obj"));
	Shader shader(shaders.load(path + ".vShader", path + ".pShader"));

	Object object = Object(mesh, texture, shader);
	return object;

}
