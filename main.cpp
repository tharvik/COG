#include "opengl.h"

#include "config.h"
#include "Game.h"

void initLibraries(int *argc, char *argv[]);
void openWindow(int &&x, int &&y, int &&width, int &&height,
                std::string &&title);
void setUpOpenGL();

int main(int argc, char *argv[])
{
        initLibraries(&argc, argv);
        
        if (GAME_MODE)
                glutEnterGameMode();
        else
                openWindow(WIN_X, WIN_Y, WIN_W, WIN_H, WIN_T);
        
        setUpOpenGL();
        
        Planet test("test");
        
//      Game game;
//	game.enterMainMenu();
        
	return 0;
}

void initLibraries(int *argc, char *argv[])
{
        // GLUT library
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
}

void openWindow(int &&x, int &&y, int &&width, int &&height,
                std::string &&title)
{
        glutInitWindowSize(width, height);
        glutInitWindowPosition(x, y);
        glutCreateWindow(title.c_str());
        glutHideWindow();

#ifndef __APPLE__
	GLenum err = glewInit();
	if (err != GLEW_OK)
		logger::error(std::string("Fail to init glew: ") +
				((char*) glewGetErrorString(err)), FL);
#endif
}

void setUpOpenGL()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_MODELVIEW);
        gluPerspective(FOV, (GLdouble) glutGet(GLUT_WINDOW_WIDTH) /
                       glutGet(GLUT_WINDOW_HEIGHT), NEAREST, FAREST);
}
