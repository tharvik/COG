#include "Object.h"
#include "config.h"

using namespace std;

map<string, shared_ptr<Material>> Object::materials;
map<string, shared_ptr<Mesh>> Object::meshes;


void Object::findNameAndExtension(const std::string& path, std::string& name,
                                  std::string& extension)
{
        name = path.substr(path.rfind('/') + 1, path.size());
        const size_t pointPosition = name.rfind('.');
        cout << name << " :" << pointPosition << endl;
        if (pointPosition != 0) {
                extension = name.substr(pointPosition + 1, path.size());
                name = name.substr(0, pointPosition);
        } else {
                extension = "";
        }
}

void Object::addMltToDrawList(const std::string& path, const std::string& name,
                              const std::string& objectPath)
{
        map<string, shared_ptr<Material>>::iterator material
                                                         = materials.find(name);
        if (material == materials.end()) {
                material = get<0>(materials.insert(make_pair(name,
                        shared_ptr<Material>(new Material(path, "path2", "3#")))));
        }
        
        drawList.push_back(make_pair(materials[name],
                                     vector<shared_ptr<Mesh>>()));
}

Object::Object(const std::string& name) : drawList()
{
	// Pathes
        const string localDir  = "Resources/objects/" + name + "/";
	const string globalDir = "Resources/";
	
	string material, vs, fs;
	
	// open object file
	ifstream file(localDir + name + ".object");
	if (!file.good())
	{
		logger::error("Unable to open object file " + name, _FL_);
	}
	
	// read object file (+ execution)
	bool local = false, inGroup;
	string word, extension;

	while (file >> word)
	{
		if (word == "#") {
			local = true;
		} else if (word == "[") { // begin group
			inGroup = true;
		} else if (word == "]"){ // end group, mesh+mtl+shaders creation
			
			Material mat = Material(material, vs, fs);
			
			material = "", vs = "", fs = "";
			inGroup = false;
		} else {
			extension = word.substr(word.find_last_of(".")+1);
			if (extension == "mesh") {		// mesh
				local = false;
			} else if (extension == "mbf") {	// material
				material = local ? localDir + word
				: globalDir + "materials/" + word;
				local = false;
			} else if (extension == "vs") {		// vertex shader
				local = false;				
			} else if (extension == "fs") {		// frag. shader
				local = false;
			} else {
				cout << "Unknown format" << endl;
			}
		}
	}
}

void Object::draw() const
{
        for (const auto& material : drawList) {
                material.first->print();
        }
}