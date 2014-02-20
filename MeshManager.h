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
		 * Parse a vertice
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 *
		 * \return Parsed vertice, of the given size
		 */
		template<unsigned short size>
			std::array<float, size> parseV();

		/**
		 * Parse a face
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 *
		 * \return Parsed face
		 */
		std::array<std::array<unsigned int, 2>, 3> parseF();

		/**
		 * Discard the remaining line
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 *
		 * \param word The parsing word
		 * \param log True if we have to logger the remaining line
		 */
		void cleanLine(const std::string& word, const bool log);

		/**
		 * Map of already loaded file
		 */
		std::map<std::string,Mesh> map;

		/**
		 * Last loaded path
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 */
		std::string path;

		/**
		 * Current loaded file, is valid during execution of \ref load
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 */
		std::ifstream file;

		/**
		 * Current parsing line, give an error line
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 */
		unsigned short lineCount;

	public:
		/**
		 * Load a .mesh file, temporary and draft function to avoid
		 * breaking existing code
		 *
		 * \deprecated After moving to .mesh file, we won't need this
		 * anymore
		 *
		 * \param path to load the .mesh from
		 *
		 * \return A reference to the wanted Mesh
		 */
		Mesh& loadMesh(const std::string& path);

		/**
		 * Load the file at the given path
		 *
		 * \param path to load the .obj from
		 *
		 * \return A reference to the wanted Mesh
		 */
		Mesh& load(const std::string& path);
};
