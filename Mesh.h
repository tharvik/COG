#pragma once

#include <array>
#include "opengl.h"
#include <string>
#include <vector>

/**
 * Represent a set of verticles and faces to draw
 *
 * Used by Object which handle Texture and Shader
 */
class Mesh {
private:
        /**
         * Number of indices to draw
         */
	unsigned int sizeIndices;
        
        /**
         * Buffers used by OpenGL
         *
         * buffers[0] contains the vertices\n
         * buffers[1] contains the vertices on the texture\n
         * buffers[2] contains the normals\n
         * buffers[3] contains the indices\n
         */
        std::array<GLuint,4> buffers;
        	
public:
        /**
         * Default constructor
         */
        Mesh();
        
        Mesh(const Mesh&) = delete;
        
        /**
         * Move constructor
         *
         * Leave m in a valid but useless state
         *
         * \param m Mesh to move, which will be left in the default
         * state
         */
        Mesh(Mesh&& mesh);
        
	/**
         * Constructor
         *
         * load a .mesh file
         *
         * \param filePath path to the .mesh file
         */
        Mesh(const std::string& filePath);
        
        /**
         * Construct with the given vertices, vertices on the texture
         * and indices
         *
         * \deprecated
         * By moving to .mesh file in MeshManager, we are leaving
         * this uneeded constructor
         *
         * \param v Vertices
         * \param vt Vertices on the texture
         * \param indices Indices to write
         */
        Mesh(const std::vector<std::array<float, 3>>& v,
             const std::vector<std::array<float, 2>>& vt,
             const std::vector<unsigned int>& indices);
        
        /**
         * Construct with the given buffers and number of indices
         *
         * \param buffers Buffers initialized and filled as \ref buffers
         *
         * \param sizeIndices Number of indices to draw
         */
        Mesh(const std::array<GLuint,4>& buffers,
             const unsigned int sizeIndices);
        
        /**
         * Draw itself
         *
         * Bettre use it after binding the texture
         */
        void draw() const;
        
        /**
         * Implement the less operator based on the values of the
         * buffers
         *
         * \param m Other mesh to compare to
         *
         * \return Return true if \f$ \sum_{i=0}^{4} buffers_i.size() < \sum_{i=0}^{4} b.buffers_i.size()\f$
         */
        bool operator<(const Mesh &m) const;
        
        /**
         * Delete the allocated buffers
         */
        ~Mesh();
};
