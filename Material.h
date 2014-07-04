#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <tuple>
#include <vector>

#include "Shader.h"
#include "Texture.h"


class Material {
private:
	// shared shaders and textures
	static std::map<std::string, std::shared_ptr<Shader>>  shaders;
        static std::map<std::string, std::shared_ptr<Texture>> textures;
        
	// used shader and textures
        std::shared_ptr<Shader> shaderToDraw;
        std::vector<std::shared_ptr<Texture>> textureToDraw;
        
	// parameters
	float Ka[3]; // ambient color
	float Kd[3]; // diffuse color
	float Ks[3]; // specular color
	float Ns;    // specular coeficient
	float d;     // transparency
	
	// textures
	std::shared_ptr<Texture> map_Ka,   // ambient color texture
				 map_Kd,   // diffuse color texture
				 map_Ks,   // specular color texture
				 map_Ns,   // specular intensity texture
				 map_d,	   // transparency texture
				 map_bump; // normal map texture
				 
	/**
	 * parse a mtl file and fill the private parameters + textures
	 * \param filePath path of the mtl file
	 */
	 void parseMtl(const std::string& filePath);
public:
	/**
	 * Constructor
	 * \param mtlPath path to the .mtl file
	 * \param vsPath path to the vertex shader
	 * \param fsPath path to the fragment shader
	 */
        Material(const std::string& mtlPath, const std::string& vsPath,
		 const std::string& fsPath);
	
	/**
	 * Unable copy
	 */
        Material(const Material&) = delete;
	
	/**
	 * Link a material
	 */
        Material(const Material&&);
        
	/**
	 * print the informations of the shader
	 */
        void print() const;
};
