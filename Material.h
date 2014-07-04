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
        
public:
	/**
	 * Constructor
	 * \param mtlPath path to the .mtl file
	 * \param vsPath path to the vertex shader
	 * \param fsPath path to the fragment shader
	 */
        Material(const std::string& mtlPath, const std::string vsPath,
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
