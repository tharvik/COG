#pragma once

#include "Logger.h"
#include <map>
#include <string>

#include "Shader.h"

class ShaderManager {
private:
        std::map<std::string,Shader> map;
        
public:
        // Constructor
        ShaderManager();
        
        Shader& load(std::string&& pathV, std::string&& pathP);
        
        // Destructor
        ~ShaderManager();
};
