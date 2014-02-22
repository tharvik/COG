#pragma once

#include <fstream>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "Logger.h"
#include "Mesh.h"

/**
 * Manage Mesh, avoid reloading a Mesh if already done
 */
class MeshManager {
	private:
		/**
		 * Map of already loaded file
		 */
		std::map<std::string,Mesh> map;

	public:
		/**
		 * Construct an empty and unusable Mesh
		 */
		MeshManager();

		/**
		 * Load a .mesh file, temporary and draft function to avoid
		 * breaking existing code
		 *
		 * \param path to load the .mesh from
		 *
		 * \return A reference to the wanted Mesh
		 */
		Mesh& load(const std::string& path);
};
