#pragma once

#include <fstream>
#include "opengl.h"

#include "Logger.h"

class Shader {
private:
	GLuint vertexShader, pixelShader, program;

	void createShaders(const std::string&  vShaderPath,
			const std::string&  pShaderPath);
	char* loadFileASCII(const std::string& filePath);
	void compileShaders(const std::string& vShaderPath,
			const std::string& pShaderPath);
	void createProgram(const std::string& vShaderPath,
			const std::string& pShaderPath);
	void linkProgram(const std::string& vShaderPath,
			const std::string& pShaderPath);
	
public:
	// Constructors
	Shader();
	Shader(const std::string& vShaderPath, const std::string& pShaderPath);
	Shader(const std::string&& vShaderPath,
			const std::string&& pShaderPath);

	void use();
	
	// Getters
	GLuint getShaderId() const;
	GLuint getvShaderId() const;
	GLuint getpShaderId() const;

	bool operator<(const Shader &b) const;
        
        // Destructor
        ~Shader();
};
