#include "Object.h"

#include <fstream>

#include "opengl.h"
#include "config.h"
#include "Logger.h"

using namespace std;

map<string, shared_ptr<Mesh>> Object::meshes;
map<string, shared_ptr<Material>> Object::materials;

Object::Object(const std::string& name)
{
	string localDir = "Resources/objects/" + name + "/";
	loadObjectFile(localDir, localDir + name + ".object");
	
	logger::info("Object '" + name + "' created", _FL_);

}

Object::~Object()
{
}

void Object::loadObjectFile(const string& localDir, const string& filePath)
{
	string word, ext;
	ifstream file(filePath);
	array<string, 4> pathes = {{"", "", "", ""}};
	bool local;

	// Pathes
	const string globalDir = "Resources/";
	
	// open file
	if (!file.good())
		logger::error("Unable to load object file " + filePath, _FL_);
	
	while (file >> word) {
		if (word == "#")
			local = true;
		
		else if (word == "]") {
			addPair(pathes);
			for (unsigned char i = 0; i < 4; i++)
				pathes[i] = "";
			local = false;
		} else {
			ext = word.substr(word.find_last_of(".")+1);
			
			if (ext == "mesh")		// mesh
				pathes[0] = local ? localDir + word
				: globalDir + "meshes/" + word;
			
			else if (ext == "mbf")		// material
				pathes[1] = local ? localDir + word
				: globalDir + "materials/" + word;
			
			else if (ext == "vs")		// vs
				pathes[2] = local ? localDir + word
				: globalDir + "shaders/" + word;
			
			else if (ext == "fs")		// fs
				pathes[3] = local ? localDir + word
				: globalDir + "shaders/" + word;
			
			else if (ext != "[")
				logger::warn("Unknown format '" + ext + "' in"
					     ".object file", _FL_);
			
			local = false;
		}
	}
	file.close();
}

void Object::addPair(const string& meshFilePath,
		     const string& mbfFilePath,
		     const string& vsFilePath,
		     const string& fsFilePath)
{
	addPair(array<string, 4>({{meshFilePath, mbfFilePath,
				  vsFilePath, fsFilePath}}));
}

void Object::addPair(const array<std::string, 4>& pathes)
{
	shared_ptr<Mesh> mesh;
	shared_ptr<Material> mtl;

/* mesh */
	
	// check if mesh already exists
	map<string, shared_ptr<Mesh>>::iterator it1;
	it1 = meshes.find(pathes[0]);
	
	// if doesn't exist create mesh
	if (it1 == meshes.end()) {
		mesh = shared_ptr<Mesh>((new Mesh(pathes[0])));
		meshes[pathes[0]] = mesh;
	}
	
/* material + shader */
	// check if material already exists
	map<string, shared_ptr<Material>>::iterator it2;
	it2 = materials.find(pathes[1] + " " + pathes[2] + " " + pathes[3]);
	
	// if doesn't exist create material
	if (it2 == materials.end()) {
		mtl = shared_ptr<Material>((new Material(pathes[1], pathes[2], pathes[3])));
		materials[pathes[1] + " " + pathes[2] + " " + pathes[3]] = mtl;
	}	
	
	// add pair
	pair<shared_ptr<Material>, shared_ptr<Mesh>> pair(mtl, mesh);
	drawList.push_back(pair);
}


void Object::draw() const
{
        for (const auto& pair : drawList) {
                pair.first->use();
		pair.second->draw();
        }
}
