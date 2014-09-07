#pragma once

#include <map>
#include <array>

#include "Texture.h"


//-------------------------------- Materials ---------------------------------//
//									      //
// A material  referes to  the apparence  of an OpenGL face.   It specifies a //
// OpenGl program (vertex shader + fragment shader) and his parameters.       //
//									      //
// The basic parameters are:						      //
//	-     Ka: vec3 ambient color					      //
//	-     Kd: vec3 diffuse color					      //
//	-     Ks: vec3 specular color					      //
//	-     Ns: float specular coeficient color			      //
//	-      d: float transparency					      //
//	- map_ka: Texture ambient color					      //
//	- map_Kd: Texture diffuse color					      //
//	- map_Ks: Texture specular color				      //
//	-  map_d: Texture transparency					      //
//									      //
// The material parameters are stored in a .mbf (material binary file) file.  //
//									      //
// All material textures  are stored in a static map   called "container" and //
// shared between the materials to avoid duplications. The GLSL sampler2D are //
// set according to the following list:					      //
//	-   map_Ka: GL_TEXTURE0						      //
//	-   map_Kd: GL_TEXTURE1						      //
//	-   map_Ks: GL_TEXTURE2						      //
//	-   map_Ns: GL_TEXTURE3						      //
//	-    map_d: GL_TEXTURE4						      //
//	- map_bump: GL_TEXTURE5						      //
//									      //
// When an material is created,  a specific OpenGl program is compile and set //
// with its basic parameters.						      //
//----------------------------------------------------------------------------//


class Material {
private:

	typedef enum
	{
		Ka = 0,
		Kd = 3,
		Ks = 6,
		Ns = 9,
		d  = 10, 
	} uniforms;
	
	typedef enum
	{
		map_Ka   = 0,
		map_Kd   = 1,
		map_Ks   = 2,
		map_Ns   = 3,
		map_d    = 4,
		map_bump = 5 
	} uniform_maps;

	/**
	 * containers
	 */
        static std::map<std::string, std::shared_ptr<Texture>>texturesCont;
	
	/**
	 * textures (map_Ka, map_Kd, map_Ks, map_Ns, map_d, map_bump) 
	 */
        std::array<std::shared_ptr<Texture>, 6> textures;
        
	/**
	 * openGL uniforms location of the basic parameters (Ka, Kd, Ks, Ns, d)
	 */
	std::array<GLint, 5> paramLoc;
	
	/**
	 * openGL uniform location of the samplers (map_Ka, map_Kd, map_Ks,
	 * map_Ns, map_d, map_bump)
	 */
	std::array<GLint, 6> samplerLoc;
	
	/**
	 * openGl references to the program 
	 */
        GLuint program;
	
	/**
	 * create openGL program from a vs and a fs
	 *
	 * \param vsPath path to the vertex shader
	 * \param fsPath path to the fragment shader
	 */
	void loadShader(const std::string& vsPath, const std::string& fsPath);
	
	/**
	 * read the material binary file and fill the private
	 * parameters + textures
	 *
	 * \param filePath path of the material binary file
	 */
	void loadMaterial(const std::string& mtlPath);
	
	/**
	 * Get the OpenGl locations of uniforms sampler (textures) and basic
	 * uniforms parameters
	 */
	void getBasicUniformsLocation();
	
	/**
         * set all basic uniform variables values
         *
         * \param values the values in this order: Ka, Kd, Ks, Ns, d
         */
	void setUniformValue(std::array<float, 11> values) const;
	
public:
	
	/**
	 * construct from a mbf, a vs and fs file
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
	 * destructor
	 */
	 ~Material();
	
	/**
	 * bind material to OpenGL
	 */
	void use() const;
	
	/**
	 * print the informations of the material
	 */
        void print() const;
};
