//
//  Shader.h
//  COG
//

#ifndef COG_Shader_h
#define COG_Shader_h

#include <iostream>
#include "opengl.h"
#include <fstream>

#include "Logger.h"

class Shader {

private:
	GLuint vertexShader, pixelShader, program;

	void createShaders(std::string&  vShaderPath, std::string&  pShaderPath);
	char* loadFileASCII(std::string& filePath);
	void compileShaders(std::string& vShaderPath, std::string& pShaderPath);
	void createProgram(std::string& vShaderPath, std::string& pShaderPath);
	void linkProgram(std::string& vShaderPath, std::string& pShaderPath);
	
public:
	// constructors
	Shader();
	Shader(std::string& vShaderPath, std::string& pShaderPath);
	Shader(std::string&& vShaderPath, std::string&& pShaderPath);

	void use();
	
	// getters
	GLuint getShaderId();
	GLuint getvShaderId();
	GLuint getpShaderId();
};

#endif
