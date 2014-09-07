#include "utilities.h"

#include <fstream>

#include "Logger.h"

using namespace std;

bool optionsStatut8b(const char options, const unsigned char p)
{
	return (options >> p) % 2;
}

string readString(ifstream& file)
{
	char* cString;
	unsigned short size;

	// read size
	file.read(reinterpret_cast<char*>(&size), sizeof(size));
	
	// allocate string
	cString = reinterpret_cast<char*>(malloc(70));
	
	// read and add end of string character
	file.read(cString, size * sizeof(char));
	cString[size] = '\0';
	
	// return a C++ string
	string str = string(cString);
	free(cString);

	return str;
}

char* loadFileASCII(const string& filePath)
{
	unsigned long length;
	ifstream file(filePath, ios::ate);
	
	if (!file.good()) {
		logger_error("Unable to open shader file '" + filePath + "'."
			      "The file may be empty or simply does not exist");
		return NULL;
	}
	
	// get file length
	length = (unsigned long) file.tellg();
	
	file.seekg(0, ios::beg);
	
	// transmit chars from the file to the string
	char* str = reinterpret_cast<char*>(malloc((length + 1) * sizeof(char)));
	if (str == nullptr) {
		logger_warn("Unable to load string from file " + filePath);
		return NULL;
	}
	file.read(str, (long) length);

	// adding \0 at the of the string
	str[length] = '\0';
	
	// clean up
	file.close();
		
	return str;
}
