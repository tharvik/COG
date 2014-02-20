#include "ShaderManager.h"

Shader& ShaderManager::load(const std::string& pathV,
		const std::string& pathP)
{
	const auto iter = this->map.find(pathV + pathP);

	if(iter == this->map.end()) {
		this->map[pathV + pathP] = Shader(pathV, pathP);
 		return this->map[pathV + pathP];
	} else {
		return iter->second;
	}
}
