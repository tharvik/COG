#pragma once

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"
#include "Material.h"

//--------------------------------- Objects ----------------------------------//
//									      //
// An object is any body shown in the OpenGl space. Each object are made of   //
// pairs (material + mesh).						      //
//									      //
// A pairs is a part of the objects with the a mesh and a material,	      //
//									      //
// The mehses and the materials are stored in 2 seperate static map called    //
// "containers" and shared between the objects to avoid the duplication of    //
// those elements.							      //
//									      //
// When an objects is drawn, each pair is send to OpenGl.		      //
//----------------------------------------------------------------------------//

class Object {
private:
	// containers
        static std::map<std::string, std::shared_ptr<Mesh>> meshes;
	static std::map<std::string, std::shared_ptr<Material>> materials;

        
	// pairs (material + mesh)
        std::vector<std::pair<std::shared_ptr<Material>,
			      std::shared_ptr<Mesh>>> drawList;
        
	/**
         * execute a .object file (add paires)
         *
         * \param localDir path to the local directory
         * \param filePath path to the object file
         */
	void loadObjectFile(const std::string& localDir,
			    const std::string& filePath);

	/**
         * adding a new pair (material + mesh) int the drawList
         *
         * \param meshFilePath path to the .mesh file
         * \param mbfFilePath path to the .mbf file
         * \param vsFilePath path to the .vs (vertex shader) file
         * \param fsFilePath path to the .fs (fragment shader) file
	 * path and the .fs file path in an array
         */
	void addPair(const std::string& meshFilePath,
		     const std::string& mbfFilePath,
		     const std::string& vsFilePath,
		     const std::string& fsFilePath);
		     
	/**
         * adding a new pair (material + mesh) int the drawList
         *
         * \param pathes an array with respectively the path to the .mesh file,
	 * the .mbf file, the .vs file and the .fs file
         */
	void addPair(const std::array<std::string, 4>& pathes);

public:
	/**
         * constructor
         */
        Object(const std::string& name);
	
	/**
         * destructor
         */
	~Object();

	/**
         * draw the drawList (material + mesh)
         */
	void draw() const;
};

