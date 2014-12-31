#include "opengl.h"

#include "config.h"
#include "Game.h"

void initLibraries(int *argc, char *argv[]);
void openWindow(int &&x, int &&y, int &&width, int &&height,
                std::string &&title);
                
int main(int argc, char *argv[])
{
        initLibraries(&argc, argv);

	openWindow(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y,
		   WINDOW_WIDTH, WINDOW_HEIGHT, PACKAGE_NAME);
				        
	Game game;
        
	return EXIT_SUCCESS;
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
		logger_error(std::string("Fail to init glew: ") +
				((char*) glewGetErrorString(err)));
#endif
}
