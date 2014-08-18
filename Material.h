#pragma once

#include <map>
#include <vector>
#include <array>

#include "Shader.h"
#include "Texture.h"

#include <memory>

/**
 * A material  referes to  the apparence  of an OpenGL face.   It specifies a
 * OpenGl program (vertex shader + fragment shader) and his parameters.
 *
 * The basic parameters are:
 *	-     Ka: vec3 ambient color
 *	-     Kd: vec3 diffuse color
 *	-     Ks: vec3 specular color
 *	-     Ns: float specular coeficient color
 *	-      d: float transparency
 *	- map_ka: Texture ambient color
 *	- map_Kd: Texture diffuse color
 *	- map_Ks: Texture specular color
 *	-  map_d: Texture transparency
 *
 * The material parameters are stored in a .mbf (material binary file) file.
 *
 * All material textures  are stored in a static map   called "container" and
 * shared between the materials to avoid duplications.
 *
 * When an material is created,  a specific OpenGl program is compile and set
 * with its basic parameters.
 */
class Material {
private:
	// containers
        static std::map<std::string, std::shared_ptr<Texture>> textures;
        
	// OpenGL program + textures
	Shader shader;
        std::vector<std::shared_ptr<Texture>> texturesToDraw;
        
	// material parameters
	// Ka[3] (ambient color), Kd[3] (diffuse color), Ks[3] specular color,
	// Ns (specular coeficient), d (transparency)
	std::array<float, 11> parameters;
					 
	/**
	 * Read the material binary file and fill the private
	 * parameters + textures
	 *
	 * \param filePath path of the material binary file
	 */
	 void readMaterialFile(const std::string& filePath);
	 	 
public:
	/**
	 * constructor
	 *
	 * \param mbfPath path to the material binary file
	 * \param vsPath path to the vertex shader
	 * \param fsPath path to the fragment shader
	 */
        Material(const std::string& mbfPath, const std::string& vsPath,
		 const std::string& fsPath);
	
	/**
	 * unable copy
	 */
        Material(const Material&) = delete;
	
	/**
	 * move constructor
	 */
        Material(const Material&&);
        
	/**
	 * bind material to OpenGL
	 */
	void use() const;
	
	/**
	 * print the informations of the material
	 */
        void print() const;
};
