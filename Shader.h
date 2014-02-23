#pragma once

#include "opengl.h"
#include <string>

class Shader {
	private:

		/**
		 * Reference to the vertex Shader in OpenGL
		 */
		GLuint vertexShader;

		/**
		 * Reference to the pixel Shader in OpenGL
		 */
		GLuint pixelShader;

		/**
		 * Reference to the program in OpenGL
		 */
		GLuint program;

		/**
		 * Create vertexShader and pixelShader, add load the given files
		 *
		 * \param vShaderPath Path to the vertex shader file
		 * \param pShaderPath Path to the pixel shader file
		 */
		void createShaders(const std::string&  vShaderPath,
				const std::string&  pShaderPath);

		/**
		 * Give a path, return a maollced buffer to the content of the
		 * file
		 *
		 * To avoid leak, the returnen buffer have to be freed
		 *
		 * \param filePath File to load
		 *
		 * \return Malloced buffer to the content of the file, have to
		 * be freed
		 */
		char* loadFileASCII(const std::string& filePath);

		/**
		 * Compile the previously initilaized shaders
		 *
		 * Should be used after createShaders
		 *
		 * \param vShaderPath Path to the vertex shader (used in Logger)
		 * \param pShaderPath Path to the pixel shader (used in Logger)
		 */
		void compileShaders(const std::string& vShaderPath,
				const std::string& pShaderPath);

		/**
		 * Create the program and attach the shaders
		 *
		 * Should be used after compileShaders
		 *
		 * \param vShaderPath Path to the vertex shader (used in Logger)
		 * \param pShaderPath Path to the pixel shader (used in Logger)
		 */
		void createProgram(const std::string& vShaderPath,
				const std::string& pShaderPath);
		/**
		 * Link the program
		 *
		 * Should be used after createProgram
		 *
		 * \param vShaderPath Path to the vertex shader (used in Logger)
		 * \param pShaderPath Path to the pixel shader (used in Logger)
		 */
		void linkProgram(const std::string& vShaderPath,
				const std::string& pShaderPath);

	public:
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

		/**
		 * Construct a Shader with the given path to the vertex shader
		 * file and pixel shader path
		 *
		 * \param vShaderPath Path to the vertex shader file
		 * \param pShaderPath Path to the pixel shader file
		 */
		Shader(const std::string& vShaderPath,
				const std::string& pShaderPath);

		/**
		 * Use the shader's program
		 */
		void use();

		/**
		 * Return the \ref program
		 *
		 * \return Copy of the \ref program
		 */
		GLuint getShaderId() const;

		/**
		 * Return the \ref vertexShader
		 *
		 * \return Copy of the \ref vertexShader
		 */
		GLuint getvShaderId() const;

		/**
		 * Return the \ref pixelShader
		 *
		 * \return Copy of the \ref pixelShader
		 */
		GLuint getpShaderId() const;

		/**
		 * Give a way to sort Shader, less operator
		 *
		 * \param b Shader to compare to
		 *
		 * \return True if the sum of the vertexShader and pixelShader
		 * is less than the one of b
		 */
		bool operator<(const Shader &b) const;
};
