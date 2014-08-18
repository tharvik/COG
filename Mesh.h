#pragma once

#include "opengl.h"
#include <array>
#include <string>
#include <vector>
#include <fstream>

#include "config.h"
#include "Vvector.h"

/**
 * A mesh referes to a set of faces, UV vertices and normals to draw.  A mesh
 * uses  the power  of the openGL VBO indexing.  It means that  all vertices,
 * UV vertices and normals  are stored in openGL buffers and an index "links"
 * them to makes faces.
 *
 * A mesh have a multi-resolution system.  A mesh far from a camera will have
 * a lower quality  than a mesh  near the camera  (less faces will be drawn).
 * The resolution is called "level":
 *	- level 1 : best quality
 *	- level 2 : good quality
 *	- level 3 : medium quality
 *	- level 4 : bad quality
 *	- level 5 : worst quality
 *
 * To assure this multi-resolution system,  the notion of mesh radius have to
 * be instored. It's precisly the distance between the center of the mesh and
 * the farest point. It assures the same treatment to a sphere and a cuboid.
 *
 * The distances for the mesh levels  can be setted by changing in the config
 * file the values of MESH_LEVEL_DISTANCES.
 *
 */
class Mesh {
private:

        /**
         * mesh radius
         */
	float radius;
	
        /**
         * number of indices to draw for each mesh levels
         */
	std::array<unsigned int, 5> sizeIndices;
        
        /**
         * buffers used by OpenGL
         *
         * buffers[x][0] contains the vertices of the level x
         * buffers[x][1] contains the UV vertices of the level x
         * buffers[x][2] contains the normals of the level x
         * buffers[x][3] contains the indices of the level x
         */
        std::array<std::array<GLuint,4>,5> buffers;
	
        /**
         * fill a buffer of elements T with the next block of a stream 
         *
	 * \param buffer openGL reference of a writeable buffer of elements T
	 * \param file the stream containing the block
	 * 
	 * \return the size (number of elements) of the block
	 */
	template<typename T>
	static unsigned int fillBuffer(GLuint buffer, std::ifstream& file);

public:
	
        /**
         * default constructor
         */
        Mesh();
        
	/**
	 * Deleted copy constructor
	 */
        Mesh(const Mesh&) = delete;
        
        /**
         * move constructor. Leave m in a valid but useless state
         *
         * \param m mesh to move, which will be left in the default
         * state
	 *
	 * \attention the function has never been tested
         */
        Mesh(Mesh&& m);
        
	/**
         * constructor
         *
         * load a .mesh file
         *
         * \param filePath path to the .mesh file
         */
        Mesh(const std::string& filePath);
        
        /**
         * construct with the given vertices, UV vertices and indices for each
         * mesh level
         *
         * \param v vertices
         * \param vt vertices on the texture
         * \param indices indices to write
         * \param rad radius of the mesh
	 *
	 * \attention the function has never been tested
         */
        Mesh(const std::array<std::vector<std::array<float, 3>>, 5>& v,
             const std::array<std::vector<std::array<float, 2>>, 5>& vt,
             const std::array<std::vector<unsigned int>, 5>& indices,
	     const float rad);
                
	/**
         * draw the faces (send faces to openGL)
	 *
	 * \param level specifie the mesh level to draw
         */
	void draw(const uint8_t level) const;
        
        /**
         * implement the less operator based on the values of the
         * buffers
         *
         * \param m other mesh to compare to
         *
         * \return return true if \f$ \sum_{i=0}^{4} buffers_i.size() < \sum_{i=0}^{4} b.buffers_i.size()\f$
         */
        bool operator<(const Mesh &m) const;
        
	/**
         * get the mesh radius
	 *
	 * \return mesh radius
         */
	float getRadius();

        /**
         * delete the allocated buffers
	 *
	 * \attention the function has never been tested
         */
        ~Mesh();
};
