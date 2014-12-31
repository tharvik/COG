#include "Renderer.h"

#include "opengl.h"
#include "Game.h"
#include "Camera.h"
#include <memory>

using namespace std;

Renderer::Renderer()
{
	
}

void Renderer::render() const
{	
	for (const unique_ptr<Object>& object
					  : Game::universe.getObjects())
		object->draw();
}

void Renderer::setUpOpenGL()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);					// useless?
        gluPerspective(FOV, GLdouble(glutGet(GLUT_WINDOW_WIDTH) /
                       glutGet(GLUT_WINDOW_HEIGHT)), NEAREST, FAREST);	// useless?
	
	// for VBO indexing	       
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
}
