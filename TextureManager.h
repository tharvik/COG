#pragma once

#include <string>
#include <map>

#include "Texture.h"

class TextureManager {

	public:
		Texture& load(const std::string path);

	private:
		std::map<std::string,Texture> map;
};
