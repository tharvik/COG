#include "Material.h"
#include <stdio.h>

using namespace std;

map<string, shared_ptr<Shader>>  Material::shaders;
map<string, shared_ptr<Texture>> Material::textures;


Material::Material(const string& mtlPath, const string& vsPath,
		   const string& fsPath)
{
	FILE* file = fopen(mtlPath.c_str(), "r");
	
	size_t length;
	char* line = fgetln(file, &length);
}

Material::Material(const Material&& material)
{

}

void Material::print() const
{

}

void Material::parseMtl(const string &filePath)
{
	
}