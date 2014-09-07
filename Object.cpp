#include "Object.h"

#include <fstream>

#include "opengl.h"
#include "config.h"
#include "Logger.h"

using namespace std;

map<string, shared_ptr<Mesh>> Object::meshesCont;
map<string, shared_ptr<Material>> Object::materialsCont;

Object::Object(const std::string& name) : drawList(), p(0, 0, 0), radius(0), level(0)
{
	string localDir = "Resources/objects/" + name + "/";
	loadObjectFile(localDir, localDir + name + ".object");
	
	logger_info("Object '" + name + "' created");
}

Object::Object(const std::string& name, const Vvector& pos) : drawList(), p(pos), radius(0), level(0)
{
	string localDir = "Resources/objects/" + name + "/";
	loadObjectFile(localDir, localDir + name + ".object");
	
	logger_info("Object '" + name + "' created");
}

Object::~Object()
{}

void Object::calculateLevel(const Vvector& camPos)
{
	float l = (camPos - this->p).length() - this->radius;
	uint8_t i = 0;
	array<float, 5> distances = {{MESH_LEVEL_DISTANCES}};
	
	while (i < 4 && l > distances[i])
		i++;
		
	this->level = i;
}


void Object::draw() const
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(p.x(), p.y(), p.z());

	// use material and draw mesh
        for (const auto& pair : drawList) {
                pair.first->use();
		for (const auto& mesh : pair.second)
			mesh->draw(this->level);
        }
	
	glPopMatrix();
}

void Object::loadObjectFile(const string& localDir, const string& filePath)
{
	string word, ext;
	ifstream file(filePath);
	bool local;
	
	// pathes
	vector<string>meshesFilePath;
	string mbfFilePath, vsFilePath, fsFilePath;
	
	// Pathes
	const string globalDir = "Resources/";
	
	// open file
	if (!file.good())
		logger_error("Unable to load object file " + filePath);
	
	while (file >> word) {
		if (word == "#")
			local = true;
		
		else if (word == "]") {
			addPair(meshesFilePath,
				mbfFilePath,
				vsFilePath,
				fsFilePath);
				
				// reset pathes
				meshesFilePath.clear();
				mbfFilePath.clear();
				vsFilePath.clear();
				fsFilePath.clear();
			local = false;
		} else {
			ext = word.substr(word.find_last_of(".")+1);
			
			if (ext == "mesh")		// mesh
				meshesFilePath.push_back(local ? localDir + word
				: globalDir + "meshes/" + word);
			else if (ext == "mbf")	// material
				mbfFilePath = local ? localDir + word
				: globalDir + "materials/" + word;
			
			else if (ext == "vs")		// vs
				vsFilePath = local ? localDir + word
				: globalDir + "shaders/" + word;
			
			else if (ext == "fs")		// fs
				fsFilePath = local ? localDir + word
				: globalDir + "shaders/" + word;
			
			else if (ext != "[")
				logger_warn("Unknown format '" + ext + "' in"
					     ".object file");
			
			local = false;
		}
	}
	file.close();
}

void Object::addPair(const std::vector<std::string>& meshesFilePath,
		     const string& mbfFilePath,
		     const string& vsFilePath,
		     const string& fsFilePath)
{
	vector<shared_ptr<Mesh>> pairMeshes;
	shared_ptr<Material> mtl;

/* meshes */
        for (const auto& meshFilePath : meshesFilePath) {
		// check if mesh already exists
		map<string, shared_ptr<Mesh>>::iterator it1;
		it1 = meshesCont.find(meshFilePath);
		
		// if doesn't exist create mesh
		if (it1 == meshesCont.end()) {
			pairMeshes.push_back(
				shared_ptr<Mesh>((new Mesh(meshFilePath))));
			meshesCont[meshFilePath] = pairMeshes.back();
		} else
			pairMeshes.push_back(meshesCont[meshFilePath]);
	
		// calculate new radius
		float meshRadius = meshesCont[meshFilePath]->getRadius();
		if (meshRadius > this->radius)
			this->radius = meshRadius;
	}
		
/* material + shader */

	// check if material already exists
	map<string, shared_ptr<Material>>::iterator it2;
	it2 = materialsCont.find(mbfFilePath + " " + vsFilePath + " " + fsFilePath);
	
	// if doesn't exist create material
	if (it2 == materialsCont.end()) {
		mtl = shared_ptr<Material>((new Material(mbfFilePath,
							 vsFilePath,
							 fsFilePath)));
		materialsCont[mbfFilePath +" "+ vsFilePath +" "+ fsFilePath] = mtl;
	} else
		mtl = materialsCont[mbfFilePath +" "+ vsFilePath +" "+ fsFilePath];
	
	// add pair
	pair<shared_ptr<Material>, vector<shared_ptr<Mesh>>>
		pair(mtl, pairMeshes);
	drawList.push_back(pair);
}
