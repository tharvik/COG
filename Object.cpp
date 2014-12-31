#include "Object.h"

#include "config.h"
#include "Game.h"
#include "Logger.h"
#include "opengl.h"
#include "Universe.h"
#include "utilities.h"

#include <fstream>
#include <LinearMath/btVector3.h>

#define NO_NAME "* no name *"

#define OBJECT_DIR "Resources/objects/"
#define GLOBAL_MATERIAL_DIR "Resources/materials/"
#define GLOBAL_MESH_DIR "Resources/materials/"
#define EMPTY_NAME "Empty name"
#define DEFAULT_MBF_PATH ""
#define DEFAULT_MESH_PATH ""

using namespace std;

map<string, shared_ptr<Mesh>> Object::meshes;
map<string, shared_ptr<Material>> Object::materials;

Object::Object(const std::string& name) : drawList(), radius(0), level(0)
{
	string localDir = "Resources/objects/" + name + "/";
	// loadObjectFile(localDir, localDir + name + ".object");
	
        motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
        btScalar mass = 1;
        btVector3 inertia(0, 0, 0);
        collisionShape->calculateLocalInertia(mass, inertia);
        
        btRigidBody::btRigidBodyConstructionInfo constructionInfo(0, motionState, collisionShape, inertia);
        rigidBody = new btRigidBody(constructionInfo);
        
	logger_info("Object '" + name + "' created");
        Game::universe.addRigidBody(rigidBody);
        logger_info("Object '" + name + "' added to the universe");
}

Object::Object(const std::string& name, const btTransform& trans)
: drawList(), radius(0), level(0)
{
	string localDir = "Resources/objects/" + name + "/";
	// loadObjectFile(localDir, localDir + name + ".object");
	
        motionState = new btDefaultMotionState(trans);
        btScalar mass = 1;
        btVector3 inertia(0, 0, 0);
        collisionShape->calculateLocalInertia(mass, inertia);
        
        btRigidBody::btRigidBodyConstructionInfo constructionInfo(0, motionState, collisionShape, inertia);
        rigidBody = new btRigidBody(constructionInfo);
        
	logger_info("Object '" + name + "' created");
        Game::universe.addRigidBody(rigidBody);
        logger_info("Object '" + name + "' added to the universe");
}

Object::~Object()
{
        Game::universe.removeRigidBody(rigidBody); // TODO What if it wasn't in?
        delete rigidBody;
        delete collisionShape;
        delete motionState;
}

void Object::loadObjectFile(const string& localDir,
			    const string& objectName)				// Do not touch
{
	const string xmlPath = localDir + objectName + ".xml";
		
	char* xmlFile = u_loadFileASCII(xmlPath);				// to test
	if (!xmlFile)
		return;
		
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile);
	
	// nodes
	union {
		rapidxml::xml_node<>* object;
	} node0;
	union {
		rapidxml::xml_node<>* info;
		rapidxml::xml_node<>* render;
	} node1;
	
	/*	
	// object >
	if (!(node0.object = doc.first_node("object"))) {
		logger_warn("No 'object' node founded in '" + xmlPath + "'.");
		return;
	}
	
	// object > info >
	if (!(node1.info = node0.object->first_node("info"))) {
		logger_warn("No 'object > info' node founded in '"
			    + xmlPath + "'.");
		this->name = NO_NAME;
	} else {
		// object > info > name >
		this->name = getObjectName(node1.info, xmlPath);
	}
	
	// object > render >
	node1.render = node0.object->first_node("render");
	if (!node1.render) {
		logger_warn("No 'object > render' node founded in '"
			    + xmlPath + "'.");
		return;
	} else {
		if (!loadRender(node1.render, localDir, objectName) == 0)
			logger_warn("Empty render node in '" + xmlPath + "'.");
	}
	free(xmlFile);
	*/
}

unsigned short Object::loadRender(const rapidxml::xml_node<>* renderNode,
				  const string& localDir,
				  const string& objectName)			// Do not touch
{
	/*
	unsigned short nbrMaterial = 0;

	rapidxml::xml_node<>* materialNode;
	rapidxml::xml_node<>* meshNode;
		
	for (materialNode = renderNode->first_node("material");
	     materialNode;
	     materialNode = materialNode->next_sibling("material")) {
		string mbfPath;
		mbfPath = getPath(materialNode, GLOBAL_MATERIAL_DIR,
				  localDir, objectName, DEFAULT_MBF_PATH);
		Material material(mbfPath);
		vector<Mesh> meshes;
		for (meshNode = materialNode->first_node("mesh");
		     meshNode;
		     meshNode = meshNode->next_sibling("mesh")) {
			string meshPath;
			meshPath = getPath(meshNode, GLOBAL_MESH_DIR,
					   localDir, objectName,
					   DEFAULT_MESH_PATH);
			Mesh m(meshPath);
			meshes.push_back(m);
		}
		nbrMaterial++;
		
		parts.push_back(pair<Material, vector<Mesh>>(material, meshes));
	}
	
	return nbrMaterial;
	*/
        return 0;
}

void Object::calculateLevel(const btVector3& camPos)
{
        btTransform trans;
        rigidBody->getMotionState()->getWorldTransform(trans);
        const btVector3& pos = trans.getOrigin();
        
	float l = (camPos - pos).length() - this->radius;
	uint8_t i = 0;
	array<float, 5> distances = {{MESH_LEVEL_DISTANCES}};
	
	while (i < 4 && l > distances[i])
		i++;
		
	this->level = i;
}


void Object::draw() const
{
        btTransform trans;
        rigidBody->getMotionState()->getWorldTransform(trans);
        float OpenGLtrans[16];
        trans.getOpenGLMatrix(OpenGLtrans);
        
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
        glLoadMatrixf(OpenGLtrans);

	// use material and draw mesh
        for (const auto& pair : drawList) {
                pair.first->use();
		for (const auto& mesh : pair.second)
			mesh->draw(this->level);
        }
	
	glPopMatrix();
}

/*
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
*/

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
		it1 = meshes.find(meshFilePath);
		
		// if doesn't exist create mesh
		if (it1 == meshes.end()) {
			pairMeshes.push_back(
				shared_ptr<Mesh>((new Mesh(meshFilePath))));
			meshes[meshFilePath] = pairMeshes.back();
		} else
			pairMeshes.push_back(meshes[meshFilePath]);
	
		// calculate new radius
		float meshRadius = meshes[meshFilePath]->getRadius();
		if (meshRadius > this->radius)
			this->radius = meshRadius;
	}
		
/* material + shader */

	// check if material already exists
	map<string, shared_ptr<Material>>::iterator it2;
	it2 = materials.find(mbfFilePath + " " + vsFilePath + " " + fsFilePath);
	
	// if doesn't exist create material
	if (it2 == materials.end()) {
		mtl = shared_ptr<Material>((new Material(mbfFilePath,
							 vsFilePath,
							 fsFilePath)));
		materials[mbfFilePath +" "+ vsFilePath +" "+ fsFilePath] = mtl;
	} else
		mtl = materials[mbfFilePath +" "+ vsFilePath +" "+ fsFilePath];
	
	// add pair
	pair<shared_ptr<Material>, vector<shared_ptr<Mesh>>>
		pair(mtl, pairMeshes);
	drawList.push_back(pair);
}
