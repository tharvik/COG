#pragma once

#include "Logger.h"
#include <map>
#include <string>

#include "Shader.h"

/**
 * Load and return Shader
 */
class ShaderManager {
	private:
		/**
		 * Map containing the already loaded Shader
		 */
		std::map<std::string,Shader> map;

	public:
		/**
		 * Return the Shader at the given path
		 *
		 * \return The wanted Shader
		 */
		Shader& load(const std::string& pathV,
				const std::string& pathP);
};
