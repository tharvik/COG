#pragma once

#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"


class Object {
private:
        std::unordered_map<Material, const std::string> materials;
        
protected:
        std::vector<std::tuple<Material, Mesh>> drawOrder;
        
public:
        virtual void draw() const = 0;
};
