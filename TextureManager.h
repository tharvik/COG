#pragma once

#include <string>

#include "Texture.h"

class TextureManager {

	public:
		TextureManager();

		Texture load(std::string paht);
};
