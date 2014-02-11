#include "ShaderManager.h"

// Constructor
ShaderManager::ShaderManager()
{}

Shader& ShaderManager::load(const std::string pathV, const std::string pathP)
{
	const auto iter = this->map.find(pathV + pathP);

	if(iter == this->map.end()) {

		// TODO remove c_str()
		this->map[pathV + pathP] = Shader(pathV.c_str(), pathP.c_str());
 		return this->map[pathV + pathP];

	} else {
		return iter->second;
	}
}

// Destructor
ShaderManager::~ShaderManager()
{}
