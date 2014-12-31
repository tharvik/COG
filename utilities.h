#pragma once

#include <string>
#include <fstream>

#include "rapidxml/rapidxml.hpp"
#include "Logger.h"
#include "opengl.h"

/**
 * Read a number in a binary file f 
 *
 * \param f the file to read into
 * \param var Variable to fill with the number
 */
#define u_readNumber(f, var) f.read(reinterpret_cast<char*>(&var),\
				    sizeof(var) / sizeof(char))

/**
 * Get the nth binary digit of a 8 bits number
 *
 * \param param the 8 bits number
 * \param n the location of the digit strating at 0 from right to left
 */
bool u_optionsStatut8b(const uint8_t param, const unsigned char n);

/**
 * Read a binary string according to the conventions
 *
 * \param file ifstream of the file to read into
 */
std::string u_readString(std::ifstream& file);

/**
 * fill a openGL buffer of elements T with the next block of a stream 
 *
 * \param buffer openGL reference of a writeable buffer of elements T
 * \param file the stream containing the block
 * 
 * \return the size (number of elements) of the block
 */
template<typename T>
GLuint u_fillBuffer(const GLuint buffer, std::ifstream& file)
{
	// read block size
	unsigned int size;
	u_readNumber(file, size);

	// get openGL buffer pointer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(size * sizeof(T)), nullptr,
		     GL_STATIC_DRAW);
	T* vertices = reinterpret_cast<T*>(glMapBuffer(GL_ARRAY_BUFFER,
						       GL_WRITE_ONLY));
	// check
	if(vertices == nullptr)
		logger_error("Failed to allocate graphic memory");

	// fill buffer
	file.read(reinterpret_cast<char*>(vertices),
			GLsizeiptr(size * sizeof(T) / sizeof(char)));

	// unmap openGL buffer pointer
	if(!glUnmapBuffer(GL_ARRAY_BUFFER))
		logger_error("Failed to unmap buffer during .mesh loading");

	return size;
}

/**
 * get the txt file content
 *
 * \param filePath Path to the file
 */
char* u_loadFileASCII(const std::string& filePath);

// PARSING
/**
 *  Get the content of a child node.
 *  \param node The parent node.
 *  \param childName Name of the child node.
 *  \return The content of the child or NULL if the node doesn't exist.
 */
char* u_XMLgetChildContent(rapidxml::xml_node<> const * const node,
			   const std::string& childName);
			    
/**
 *  Get the path global or local path according to the 'global' attribute.
 *  \param node Node to read. It looks like : 
 *	<thing global="false" path="thing.jpg">>
 *  \param globalDir Global directory.
 *  \param localDir local directory.
 *  \return The path or NULL if the node doesn't exist or if one of the 
 * 	attributes doesn't exist
 */
char* u_XMLgetPath(rapidxml::xml_node<> const * const node,
		   const std::string& globalDir, const std::string& localDir);
