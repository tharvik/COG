#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <memory>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"


class Object {
private:
        static std::map<std::string, std::shared_ptr<Material>> materials;
        static std::map<std::string, std::shared_ptr<Mesh>>     meshes;

        std::vector<std::pair<std::shared_ptr<Material>,
                              std::shared_ptr<Mesh>>> drawOrder;

public:
        Object(const std::string& name);

        virtual void draw() const = 0;
};

