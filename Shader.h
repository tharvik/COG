#pragma once

#include <fstream>
#include "opengl.h"

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
	// Constructors
	Shader();
	Shader(std::string& vShaderPath, std::string& pShaderPath);
	Shader(std::string&& vShaderPath, std::string&& pShaderPath);

	void use();
	
	// Getters
	GLuint getShaderId();
	GLuint getvShaderId();
	GLuint getpShaderId();

	bool operator<(const Shader &b) const;
        
        // Destructor
        ~Shader();
};