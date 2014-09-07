#pragma once

#include <string>

bool optionsStatut8b(const char options, const unsigned char p);

/**
 * Read a binary string according to the conventions
 *
 * \param file ifstream of the file to read into
 */
std::string readString(std::ifstream& file);

/**
 * get the txt file content
 *
 * \param filePath Path to the file
 */
char* loadFileASCII(const std::string& filePath);
