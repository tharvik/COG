#include "Material.h"
#include "Logger.h"
#include <fstream>

using namespace std;

map<string, shared_ptr<Shader>>  Material::shaders;
map<string, shared_ptr<Texture>> Material::textures;


Material::Material(const string& mtlPath, const string& vsPath,
		   const string& fsPath)
{
	readMaterialFile(mtlPath);
}

Material::Material(const Material&& material)
{

}

void Material::print() const
{
	printf("\tKa = (%.3f %.3f %.3f)\n" \
	       "\tKd = (%.3f %.3f %.3f)\n" \
	       "\tKs = (%.3f %.3f %.3f)\n" \
	       "\tNs = %.3f\n" \
	       "\t d = %.3f\n",
	       this->parameters[Material::Ka+0],
	       this->parameters[Material::Ka+1],
	       this->parameters[Material::Ka+2],
	       this->parameters[Material::Kd+0],
	       this->parameters[Material::Kd+1],
	       this->parameters[Material::Kd+2],
	       this->parameters[Material::Ks+0],
	       this->parameters[Material::Ks+1],
	       this->parameters[Material::Ks+2],
	       this->parameters[Material::Ns],
	       this->parameters[Material::d]);
}

void Material::readMaterialFile(const string &filePath)
{
	// open file
	ifstream file;
	file.open(filePath, std::ifstream::binary);
	if (file != ios_base::goodbit)
	{
		logger::warn("Unable to open material binary file." \
			     "The file may be empty or doesn't exist.", _FL_);
		return;
	}
	
	
	// read 
	file.read((char*) parameters.data(),
		  parameters.max_size() * sizeof(float));
}
