#pragma once

#include <map>

#include "Object.h"
#include "TextureManager.h"
#include "MeshManager.h"

class ObjectManager {

	public:
		Object& load(const std::string name);

	private:
		std::map<std::string,Object> map;

		TextureManager textures;
		MeshManager meshs;
};
