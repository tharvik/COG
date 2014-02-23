#include "ShaderManager.h"

Shader& ShaderManager::load(const std::string& pathV,
		const std::string& pathP)
{
	const auto iter = this->map.find(pathV + pathP);

	if(iter == this->map.end()) {
		this->map.insert(std::make_pair(pathV + pathP,
				std::move(Shader(pathV, pathP))));
 		return this->map[pathV + pathP];
	} else {
		return iter->second;
	}
}
