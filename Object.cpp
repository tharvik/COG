#include "Object.h"

using namespace std;

map<string, shared_ptr<Material>> Object::materials;
map<string, shared_ptr<Mesh>>     Object::meshes;

// Constructors
Object::Object(const std::string& name) : drawOrder()
{
        // read file
        
        string materialName = name; // tmp
        string meshName     = name; // tmp
        
        map<string, shared_ptr<Material>>::iterator material =
                                                   materials.find(materialName);
        if (material == materials.end()) {
                material = get<0>(materials.insert(make_pair(materialName,
                            shared_ptr<Material>(new Material(materialName)))));
        }
        
        map<string, shared_ptr<Mesh>>::iterator mesh = meshes.find(meshName);
        if (mesh == meshes.end()) {
                mesh = get<0>(meshes.insert(make_pair(meshName,
                                        shared_ptr<Mesh>(new Mesh(meshName)))));
        }
        
        drawOrder.push_back(make_pair(material->second, mesh->second));
}

void Object::draw() const
{
        for (const pair<const shared_ptr<Material>, const shared_ptr<Mesh>> material : drawOrder) {
                material.first->print();
        }
}