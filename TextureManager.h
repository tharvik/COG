#pragma once

#include "Logger.h"
#include <map>
#include <string>
#include <string.h>

#include "Texture.h"

/**
 * Load and return Texture
 */
class TextureManager {
	private:
		/**
		 * Map containing the already loaded Texture
		 */
		std::map<std::string,Texture> map;

	public:
		/**
		 * Return the Texture at the given path
		 *
		 * \param path The path to load the Texture from
		 *
		 * \return The wanted Texture
		 */
		Texture& load(const std::string& path);
};
