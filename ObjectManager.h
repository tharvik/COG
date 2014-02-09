#pragma once

#include <map>

#include "Logger.h"
#include "MeshManager.h"
#include "Object.h"
#include "TextureManager.h"

class ObjectManager {
private:
        std::map<std::string,Object> map;
        
        TextureManager textures;
        MeshManager meshs;
        
public:
        // Constructor
        ObjectManager();
        
        Object& load(const std::string name);
        
        // Destructor
        ~ObjectManager();
};
