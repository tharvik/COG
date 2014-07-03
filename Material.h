#ifndef COG_Material_h
#define COG_Material_h

#include <map>

class Material {
private:
	static std::map<Shader, const std::string> shaders;
	static std::map<Texture, const std::string> textures;
	
	
public:
};

#endif
