#include "Object.h"

using namespace std;

map<std::string, Material> Object::materials;
map<std::string, Mesh>     Object::meshes;

// Constructors
Object::Object(const std::string& name) : drawOrder()
{
        // read file
        
        string materialName = "rusty";
        string meshName     = "salad";
        
        map<std::string, Material>::iterator material =
                                                   materials.find(materialName);
        map<std::string, Mesh>::iterator mesh = meshes.find(meshName);
        
        if (materials.find(materialName) != materials.end()) {
                if (meshes.find(meshName) != meshes.end()) {
                        drawOrder.push_back(make_tuple(material, mesh));
                        
                } else {
                        // load mesh
                }
                
        } else {
                // load material
        }
        
}

void Object::draw() const
{}