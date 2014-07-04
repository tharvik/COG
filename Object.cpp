#include "Object.h"

#include <sys/stat.h>

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;

map<string, shared_ptr<Material>> Object::materials;
map<string, shared_ptr<Mesh>> Object::meshes;


void Object::findNameAndExtension(const std::string& path, std::string& name,
                                  std::string& extension)
{
        name = path.substr(path.rfind('/') + 1, path.size());
        const size_t pointPosition = name.rfind('.');
        
        if (pointPosition != -1) {
                extension = name.substr(pointPosition + 1, path.size());
                name = name.substr(0, pointPosition);
        } else {
                extension = "";
                logger::warn("File without extension in object " + name, _FL_);
        }
}

void Object::addMltToDrawList(const std::string& path, const std::string& name,
                              const std::string& objectPath)
{
        map<string, shared_ptr<Material>>::iterator material
                                                         = materials.find(name);
        if (material == materials.end()) {
                material = get<0>(materials.insert(make_pair(name,
                        shared_ptr<Material>(new Material(path, objectPath)))));
        }
        
        drawList.push_back(make_pair(materials[name],
                                     vector<shared_ptr<Mesh>>({})));
}

Object::Object(const std::string& name) : drawList()
{
        const string Objectpath = "Resources/" + name;
        DIR *directory;
        directory = opendir(Objectpath.c_str());
        
        class dirent *ent;
        class stat sta;
        
        while ((ent = readdir(directory)) != NULL) {
                string fileName = ent->d_name;
                string filePath = Objectpath + '/' + fileName;
                string fileExtension;
                
                if (fileName.front() == '.'
                    or stat(filePath.c_str(), &sta) == -1
                    or (sta.st_mode & S_IFDIR) != 0) {
                        continue;
                }
                
                
                char tmp[1024];
                memset(tmp, '\0', 1024 * sizeof(char));
                if (readlink(filePath.c_str(), tmp, 1024) != -1) {
                        filePath = string(tmp);
                        
                        findNameAndExtension(filePath, fileName, fileExtension);
                        if (fileExtension == "mtl")
                               addMltToDrawList(filePath, fileName, Objectpath);
                }
                
//
//                ifstream objectFile;
//                string word;
//                
//                while (objectFile >> word) {
//                        if (word.back() == ':') {
//                                cout << word.substr(0, word.size() - 1);
//                        }
//                }
        }
        
        // read file
        
//        drawOrder.push_back(make_pair(Material("materialName"), vector<shared_ptr<Mesh>>({})));
        
//        string meshName = name; // tmp
//        
//        map<string, shared_ptr<Mesh>>::iterator mesh = meshes.find(meshName);
//        if (mesh == meshes.end()) {
//                mesh = get<0>(meshes.insert(make_pair(meshName,
//                                        shared_ptr<Mesh>(new Mesh(meshName)))));
//        }
//        
//        drawOrder.end()->second.push_back(mesh->second);
}

void Object::draw() const
{
        for (const auto& material : drawList) {
                material.first->print();
        }
}