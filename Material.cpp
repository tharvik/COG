#include "Material.h"

using namespace std;

map<string, shared_ptr<Shader>>  Material::shaders;
map<string, shared_ptr<Texture>> Material::textures;


Material::Material(const std::string& name)
{
        // read file
        
        string shaderName  = name; // tmp
        string textureName = name; // tmp
        
        map<string, shared_ptr<Shader>>::iterator shader =
                                                       shaders.find(shaderName);
        if (shader == shaders.end()) {
                shader = get<0>(shaders.insert(make_pair(shaderName,
                                  shared_ptr<Shader>(new Shader(shaderName)))));
        }
        
        shaderToDraw = shader->second;
        
        // while()
        map<string, shared_ptr<Texture>>::iterator texture =
                                                     textures.find(textureName);
        if (texture == textures.end()) {
                texture = get<0>(textures.insert(make_pair(textureName,
                               shared_ptr<Texture>(new Texture(textureName)))));
        }
        
        textureToDraw.push_back(texture->second);
}

Material::Material(const Material&& material)
{}

void Material::print() const
{}