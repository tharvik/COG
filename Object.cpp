#include "Object.h"

using namespace std;

map<string, shared_ptr<Material>> Object::materials;
map<string, shared_ptr<Mesh>> Object::meshes;


void Object::findNameAndExtension(const std::string& path, std::string& name,
                                  std::string& extension)
{
        name = path.substr(path.rfind('/') + 1, path.size());
        const size_t pointPosition = name.rfind('.');
        cout << name << " :" << pointPosition << endl;
        if (pointPosition != 0) {
                extension = name.substr(pointPosition + 1, path.size());
                name = name.substr(0, pointPosition);
        } else {
                extension = "";
        }
}

void Object::addMltToDrawList(const std::string& path, const std::string& name,
                              const std::string& objectPath)
{
        map<string, shared_ptr<Material>>::iterator material
                                                         = materials.find(name);
        if (material == materials.end()) {
                material = get<0>(materials.insert(make_pair(name,
                        shared_ptr<Material>(new Material(path, "path2", "3#")))));
        }
        
        drawList.push_back(make_pair(materials[name],
                                     vector<shared_ptr<Mesh>>()));
}

Object::Object(const std::string& name) : drawList()
{
	Material(name + ".mtl", name + ".vs", name + ".fs");

        const string Objectpath = "Resources/" + name;
        DIR *directory;
        directory = opendir(Objectpath.c_str());
        
        class dirent *ent;
        class stat sta;
        
        while ((ent = readdir(directory)) != NULL) {
                string fileName = ent->d_name;
                string filePath = Objectpath + '/' + fileName;
                string fileExtension;
                
                if (stat(filePath.c_str(), &sta) == -1) {
                        logger::warn("Invalid file in " + fileName + " object",
                                     _FL_);
                        continue;
                }
                
                if ((fileName.front() == '.') or (sta.st_mode & S_IFDIR) != 0)
                        continue;
                
                char tmp[1024];
                memset(tmp, '\0', 1024 * sizeof(char));
                if (readlink(filePath.c_str(), tmp, 1024) != -1) {
                        filePath = string(tmp);
                        findNameAndExtension(filePath, fileName, fileExtension);
                        if (fileExtension == "mtl")
                               addMltToDrawList(filePath, fileName, Objectpath);
                }
        }
}

void Object::draw() const
{
        for (const auto& material : drawList) {
                material.first->print();
        }
}