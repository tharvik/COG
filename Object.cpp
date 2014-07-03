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
        
        map<string, Material>::iterator material = materials.find(materialName);
        if (material == materials.end()) {
                material = get<0>(materials.insert(make_pair(materialName,
                                                move(Material(materialName)))));
        }
        
        map<string, Mesh>::iterator mesh = meshes.find(meshName);
        if (mesh == meshes.end()) {
                mesh = get<0>(meshes.insert(make_pair(meshName,
                                                        move(Mesh(meshName)))));
        }
        
        drawOrder.push_back(make_pair(material, mesh));
}

void Object::draw() const
{}