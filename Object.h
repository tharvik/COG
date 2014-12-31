#pragma once

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Material.h"
#include "rapidxml/rapidxml.hpp"

#include <BulletDynamics/btBulletDynamicsCommon.h>

class Game;

/**
 *
 * An object is any body shown in the OpenGl space. Each object are made of
 * pairs (material + mesh[]).
 *
 * A pairs is a part of the objects with the same material. It can containes
 * many meshes.
 *
 * The mehses and the materials are stored in 2 seperate static map called
 * "containers" and shared between the objects to avoid the duplication of
 * those elements.
 *
 * When an objects is drawn, each pair is send to OpenGl.
 *
 */
class Object {
private:
	std::string name = "* no name loaded*";

	void loadObjectFile(const std::string& localDir,
			    const std::string& objectName);			// Do not touch

	unsigned short loadRender(const rapidxml::xml_node<>* renderNode,
				  const std::string& localDir,
				  const std::string& objectName);		// Do not touch


	/// Map of path to loaded Mesh
        static std::map<std::string, std::shared_ptr<Mesh>> meshes;

	/// Map of path to loaded Material
	static std::map<std::string, std::shared_ptr<Material>> materials;


	// pairs (material + mesh)
	/**
	 * Vector of pair of Material and vector of Mesh, used in drawing
	 *
	 * The use of the vector is vs a set is the level, which need to be
	 * recorded
	 * The pair is because one Material can be applied to many Mesh
	 */
        std::vector<std::pair<std::shared_ptr<Material>,
			      std::vector<std::shared_ptr<Mesh>>>> drawList;
	
        btCollisionShape* collisionShape;
        btDefaultMotionState* motionState; // TODO When can we remove this?
        btRigidBody* rigidBody;
	
	// radius
	float radius;
	
	/**
	 * Current level of resolution
	 */
	uint8_t level;
        
	/**
         * execute a .object file (add paires)
         *
         * \param localDir path to the object local directory
         * \param filePath path to the object file
         */
	//void loadObjectFile(const std::string& localDir,
	//		    const std::string& filePath);

	/**
         * adding a new pair (material + mesh) into the drawList
         *
         * \param meshesFilePath	path to the .mesh file
         * \param mbfFilePath		path to the .mbf file
         * \param vsFilePath		path to the .vs (vertex shader) file
         * \param fsFilePath		path to the .fs (fragment shader) file
         */
	void addPair(const std::vector<std::string>& meshesFilePath,
		     const std::string& mbfFilePath,
		     const std::string& vsFilePath,
		     const std::string& fsFilePath);

public:
	/**
         * constructor
	 *
	 * \param name the name of the object folder
         */
        Object(const std::string& name);
	
	/**
         * constructor
	 *
	 * \param name the name of the object folder
	 * \param pos the position of the object
         */
        Object(const std::string& name, const btTransform& trans);

	/**
	* destructor
	*/
	virtual ~Object();

	/**
         * compute the mesh level needed to draw the mesh
	 *
	 * \param camPos position of the camera in the word
         */
        void calculateLevel(const btVector3& camPos);

	/**
         * draw the drawList (material + mesh)
         */
	void draw() const;
};

