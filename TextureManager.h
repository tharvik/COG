#pragma once

#include <string>
#include <map>

#include "Texture.h"

class TextureManager {

	public:
		TextureManager();

		Texture load(std::string paht);

	private:
		std::map<std::string,Texture> map;
};
