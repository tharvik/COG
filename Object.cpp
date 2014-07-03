#include "Object.h"

using namespace std;

map<string, Material> Object::materials;
map<string, Mesh>     Object::meshes;

// Constructors
Object::Object(const std::string& name) : drawOrder()
{
        // read file
        
        string materialName = "rusty";
        string meshName     = "salad";
        
        const map<std::string, Material>::iterator material =
                                                   materials.find(materialName);
        const map<std::string, Mesh>::iterator mesh = meshes.find(meshName);
        
        if (materials.find(materialName) != materials.end()) {
                if (meshes.find(meshName) != meshes.end()) {
push:                   drawOrder.push_back(make_tuple(material, mesh));
                        
                } else {
                        // load mesh
                }
                
        } else {
                materials.emplace(materialName, Material(materialName));
        }
        
}

void Object::draw() const
{

        

}