#include "Material.h"
#include "Logger.h"
#include <fstream>

using namespace std;

map<string, shared_ptr<Shader>>  Material::shaders;
map<string, shared_ptr<Texture>> Material::textures;


Material::Material(const string& mbfPath, const string& vsPath,
		   const string& fsPath)
{
	readMaterialFile(mbfPath);
	print();
	
	// check if the shader already exist
	std::map<string, shared_ptr<Shader>>::iterator it;
	it = shaders.find(vsPath + " " + fsPath);
	
	if (it == shaders.end()) { // if doesn't exist create shader
		shared_ptr<Shader> shaderPtr(new Shader(vsPath, fsPath));
		shaders[vsPath + " " + fsPath] = shaderPtr;
		logger::info("creating new shader " + vsPath + " " + fsPath, 
			     _FL_);
	}
	
	
	// set the material shader
	this->shaderToDraw = shaders[vsPath + " " + fsPath];
	
	// set uniform values to the shader
	this->shaderToDraw->setUniformValue(this->parameters);
}

Material::Material(const Material&& material)
{

}

void Material::use() const
{
	this->shaderToDraw->use();
//	this->
	
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
		logger::warn("Unable to open material binary file ." + filePath
			     + "The file may be empty or doesn't exist.", _FL_);
		return;
	}
	
	
	// read 
	file.read((char*) parameters.data(),
		  parameters.max_size() * sizeof(float));
		 
	// end
	file.close();
}
