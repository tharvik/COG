#include "Material.h"

using namespace std;

map<string, shared_ptr<Shader>>  Material::shaders;
map<string, shared_ptr<Texture>> Material::textures;


Material::Material(const std::string& mtlPath, const std::string& ObjectPath)
{}

Material::Material(const Material&& material)
{}

void Material::print() const
{}