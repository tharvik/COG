#pragma once

#include <array>
#include <string>
#include <vector>
#include <set>
#include <tuple>

#include "opengl.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

/**
 * Represent an tuple of Mesh, Texture and Shader
 */
class Object {
	private:
		/**
		 * Sub-Object, that this Object has to manage
		 */
		std::set<Object> objects;

		/**
		 * We need a new set of Mesh/Texture/Shader at every
		 * \ref resolution
		 */
		std::vector<std::tuple<Mesh*,Texture*,Shader*>> meshs;

		/**
		 * Actual resolution of drawing
		 *
		 * We want to avoid spending long time drawing far object and
		 * so, we have to know which tuple we have to draw now
		 */
		unsigned short resolution;

	public:
		/**
		 * Unusable until an object is added
		 */
		Object();

		/**
		 * Initialize with the given tuple
		 *
		 * \param mesh Mesh to use at resolution 0
		 * \param texture Texture to use at resolution 0
		 * \param shader Shader to use at resolution 0
		 */
		Object(Mesh& mesh, Texture& texture, Shader& shader);

		/**
		 * Allow ordering
		 *
		 * \param b Other Object to compare to
		 *
		 * \return true if this < &b
		 */
		bool operator<(const Object &b) const;

		/**
		 * Push back an Object to the \ref meshs
		 *
		 * \param object Object to add
		 */
		void addObject(Object& object);

		/**
		 * Erase an Object from the \ref meshs
		 *
		 * \param object Object to erase
		 */
		void delObject(Object& object);

		/**
		 * Draw at the current \ref resolution and its sub-Object
		 */
		virtual void draw() const;
};
