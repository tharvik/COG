#include "utilities.h"

#include <sstream>
#include <string.h>

using namespace std;

bool u_optionsStatut8b(const uint8_t param, const unsigned char n)
{
	return (param >> n) % 2;
}

string u_readString(ifstream& file)
{
	char* cstr;
	unsigned short size;

	// read size
	u_readNumber(file, size);
	
	// allocate string
	cstr = reinterpret_cast<char*>(malloc(size * sizeof(char)));
	
	// read
	file.read(cstr, size * sizeof(char));
	
	// return a C++ string
	string str = string(cstr, size);
	free(cstr);
	
	return str;
}

char* u_loadFileASCII(const string& filePath)
{
	ifstream file(filePath);
	
	if (!file.good()) {
		logger_error("Unable to open file '" + filePath + "'.");
		return NULL;
	}
	
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	
	char* str = (char*) malloc((content.length() + 1) * sizeof(char));
	strcpy(str, content.c_str());
	return str;

//	unsigned long length;
//	ifstream file(filePath, ios::ate);
//	
//	if (!file.good()) {
//		logger_error("Unable to open shader file '" + filePath + "'."
//			      "The file may be empty or simply does not exist");
//		return NULL;
//	}
//	
//	// get file length
//	length = (unsigned long) file.tellg();
//	
//	file.seekg(0, ios::beg);
//	
//	// transmit chars from the file to the string
//	char* str = reinterpret_cast<char*>(malloc((length + 1) * sizeof(char)));
//	if (str == nullptr) {
//		logger_warn("Unable to load string from file " + filePath);
//		return NULL;
//	}
//	file.read(str, (long) length);
//
//	// adding \0 at the of the string
//	str[length] = '\0';
//	
//	// clean up
//	file.close();
//		
//	return str;
}

char* u_XMLgetChildContent(rapidxml::xml_node<> const * const node,
			   const std::string& childName)
{
	/*
	rapidxml::xml_node<>* childNode = node->first_node(childName);
	
	if (!childNode) {
		string parentName(node.name());
		logger_warn("No child node called '" + childName +"' found in '"
			    + parentName + "' node.");
		return NULL;
	}
	
	return objNameStr;*/
        return nullptr;
}

char* u_XMLgetPath(rapidxml::xml_node<> const * const node,
		   const std::string& globalDir, const std::string& localDir)
{
	/*
	bool global = false;
	union {
		rapidxml::xml_attribute<>* global;
		rapidxml::xml_attribute<>* path;
	} attribute;
	
	attribute.global = node->first_attribute("global");
	if (attribute.global) {
		string strGlobal = string(attribute.global->value(),
					  attribute.global->value_size());
		if (strGlobal == "true") {
			global = true;
		} else if (strGlobal != "false") {
			logger_warn("Invalid global attribute in '"
				    + node.name() + "' node.");
		}
	}
	
	attribute.path = node->first_attribute("path");
	if (!attribute.path) {
		logger_warn("Missing path attribute in node in '"  + node.name()
			    + "' node.");
		return NULL;
	}
		
	string strMbfName(attribute.path->value());
		
	if (global)
		path = globalDir + strMbfName;
	else
		path = localDir + strMbfName;
	}
	
	return path;*/
        return nullptr;
}
