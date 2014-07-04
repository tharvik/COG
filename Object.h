#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <memory>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Logger.h"


class Object {
private:
        static std::map<std::string, std::shared_ptr<Material>> materials;
        static std::map<std::string, std::shared_ptr<Mesh>> meshes;
        
        std::vector<std::pair<std::shared_ptr<Material>,
                                 std::vector<std::shared_ptr<Mesh>>>> drawList;
        
        void findNameAndExtension(const std::string& path, std::string& name,
                                  std::string& extension);
        void addMltToDrawList(const std::string& path, const std::string& name,
                              const std::string& objectPath);
public:
        Object(const std::string& name);

        virtual void draw() const = 0;
};

