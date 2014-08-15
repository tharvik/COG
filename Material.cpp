#include "Material.h"

#include <fstream>

#include "Logger.h"


using namespace std;

map<string, shared_ptr<Texture>> Material::textures;

Material::Material(const string& mbfPath, const string& vsPath,
		   const string& fsPath) : shader(vsPath, fsPath)
{
	readMaterialFile(mbfPath);
		
	// set uniform values to the shader
	this->shader.setUniformValue(this->parameters);
}

Material::Material(const Material&& material) : shader(move(material.shader)),
texturesToDraw(move(material.texturesToDraw)),
parameters(move(material.parameters))
{}

void Material::use() const
{
	this->shader.use();
	
	//!! still need to use textures
}

void Material::print() const
{
	cout << "\tKa = ("
	     << this->parameters[Shader::Ka+0]
	     << this->parameters[Shader::Ka+1]
	     << this->parameters[Shader::Ka+2]
	     << ")" << endl
	     << "\tKd = ("
	     << this->parameters[Shader::Kd+0]
	     << this->parameters[Shader::Kd+1]
	     << this->parameters[Shader::Kd+2]
	     << ")" << endl
	     << "\tKs = ("
	     << this->parameters[Shader::Ks+0]
	     << this->parameters[Shader::Ks+1]
	     << this->parameters[Shader::Ks+2]
	     << ")" << endl
	     << "\tNs = " << this->parameters[Shader::Ns+0] << endl
	     << "\td = "  << this->parameters[Shader::d+0]  << endl;
}

void Material::readMaterialFile(const string &filePath)
{
	// open file
	ifstream file;
	file.open(filePath, std::ifstream::binary);
	if (!file.good())
	{
		logger_warn("Unable to open material binary file ." + filePath
			     + "The file may be empty or doesn't exist.");
		return;
	}
	
	
	// read 
	file.read((char*) parameters.data(),
		  (long) (parameters.max_size() * sizeof(float)));
		 
	// end
	file.close();
}
