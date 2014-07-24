#pragma once

#include "opengl.h"
#include <string>
#include <array>

class Shader {
private:
        // OpenGl references to vertex shader, fragment shader and program 
        GLuint vertexShader, fragmentShader, program;
        
	// Basic uniform locations
	std::array<GLint, 5> parameters;
	
        /**
         * Create vertexShader and fragmentShader, add load the given files
         *
         * \param vsPath Path to the vertex shader file
         * \param fsPath Path to the fragment shader file
         */
        void createShaders(const std::string&  vsPath,
                           const std::string&  fsPath);

        /**
         * Compile the previously initilaized shaders
         *
         * Should be used after createShaders
         *
         * \param vsPath Path to the vertex shader
         * \param fsPath Path to the fragment shader
         */
        void compileShaders(const std::string& vsPath,
                            const std::string& fsPath);
        
        /**
         * Create the program and attach the shaders
         *
         * Should be used after compileShaders
         *
         * \param vsPath Path to the vertex shader
         * \param fsPath Path to the fragment shader
         */
        void createProgram(const std::string& vsPath,
                           const std::string& fsPath);
        /**
         * Link the program
         *
         * Should be used after createProgram
         *
         * \param vsPath Path to the vertex shader
         * \param fsPath Path to the fragment shader
         */
        void linkProgram(const std::string& vsPath,
                         const std::string& fsPath);
	
        /**
         * get the basic uniforms location (Ka, Kd, Ks, Ns, d)
         *
         * \param vsPath Path to the vertex shader
         * \param fsPath Path to the fragment shader
         */
	void getBasicUniformsLocation();
		
	/**
         * get the txt file content
         *
         * \param filePath Path to the file
         */
	char* loadFileASCII(const std::string& filePath);
        
public:

typedef enum
{
	Ka = 0,
	Kd = 3,
	Ks = 6,
	Ns = 9,
	d  = 10, 
} uniforms;

        /**
         * Default constructor, valid but useless state
         */
        Shader();
        
        /**
         * Move constructor, leave the given shader in a valid but
         * useless state
         *
         * \param shader Shader to move from
         */
        Shader(Shader&& shader);
        
        Shader(const Shader&) = delete;
        
        /**
         * Construct a Shader with the given path to the vs and fs
         *
         * \param vsPath Path to the vertex shader file
         * \param fsPath Path to the fragment shader file
         */
        Shader(const std::string& vsPath,
               const std::string& fsPath);
        
        Shader(const std::string& name);
        
        /**
         * Use the shader's program
         */
        void use();
        
        
        /**
         * Give a way to sort Shader, less operator
         *
         * \param b Shader to compare to
         *
         * \return True if the sum of the vs and fs is less than the one of b
         */
        bool operator<(const Shader &b) const;
	
	/**
         * set the specified unfiform variable value
         *
         * \param uniform the uniform variable to set
         * \param value the value
         */
	void setUniformValue(Shader::uniforms uniform, float value);
	void setUniformValue(Shader::uniforms uniform,
			     float v1, float v2, float v3);
	void setUniformValue(std::array<float, 11> values);
};
