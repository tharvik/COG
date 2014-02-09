#pragma once

#include "Logger.h"
#include <map>
#include <string>
#include <string.h>

#include "Texture.h"

#include "stb_image.h"

class TextureManager {
private:
        std::map<std::string,Texture> map;
        
public:
        // Constructor
        TextureManager();
        
        Texture& load(const std::string path);
        
        // Destructor
        ~TextureManager();
};
