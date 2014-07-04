#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "Shader.h"
#include "Texture.h"


class Material {
private:
	static std::map<std::string, std::shared_ptr<Shader>>  shaders;
        static std::map<std::string, std::shared_ptr<Texture>> textures;
        
        std::shared_ptr<Shader> shaderToDraw;
        std::vector<std::shared_ptr<Texture>> textureToDraw;
        
public:
        Material(const std::string& name);
        Material(const Material&) = delete;
        Material(const Material&&);
        
        void print() const;
};
