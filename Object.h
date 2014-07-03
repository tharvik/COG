#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"


class Object {
private:
        static std::map<std::string, Material> materials;
        static std::map<std::string, Mesh>     meshes;
        
        std::vector<std::pair<const std::map<std::string, Material>::iterator,
                              const std::map<std::string, Mesh>::iterator>>
                                                                      drawOrder;
        
public:
        Object(const std::string& name);
        
        virtual void draw() const = 0;
};

