#pragma once

#include <map>

#include "Object.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

class ObjectManager {
private:
        std::map<std::string,Object> map;
        
        TextureManager textures;
        MeshManager meshs;
        ShaderManager shaders;
        
public:
        // Constructor
        ObjectManager();
        
        Object& load(const std::string name);
        
        // Destructor
        ~ObjectManager();
};
