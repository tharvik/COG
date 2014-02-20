#pragma once

#include "Object.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

/**
 * Handle loading every Object
 */
class ObjectManager {
	private:
		/**
		 * Load every Texture
		 */
		TextureManager textures;

		/**
		 * Load every Mesh
		 */
		MeshManager meshs;

		/**
		 * Load every Shader
		 */
		ShaderManager shaders;

		/**
		 * Base path to load relatively from
		 */
		const std::string path;

	public:
		/**
		 * Construct with the default path
		 */
		ObjectManager();

		/**
		 * Setup the manager to load from the given path
		 *
		 * \param path The relative \ref path
		 */
		ObjectManager(const std::string& path);

		/**
		 * Load the Object with the given name
		 *
		 * \param name The name of the Object to load
		 *
		 * \return The Object of the given name
		 */
		Object load(const std::string& name);
};
