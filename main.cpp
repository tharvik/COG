#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <SDL2/SDL.h>

#include "opengl.h"

#include "Image.cpp"
#include "ObjLoader.h"

enum {GRAPHIC_TEST, BODY_TEST};

#define MODE GRAPHIC_TEST

int initLibraries();

SDL_Window* openWindow(SDL_Rect &windowRect, string &&title);
SDL_Window* openWindow(SDL_Rect &windowRect, string &title);

void initWindow(SDL_Window *window);

void drawCube();
void refresh(SDL_Window *window);

int main(int argc, char *argv[])
{
        initLibraries();
        
        SDL_Rect mainWindowRect = {SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   800, 450};
        SDL_Window *mainWindow = openWindow(mainWindowRect, "Main Window");
        
        initWindow(mainWindow);
        
        if (MODE == BODY_TEST) {
                ObjLoader loader;
                auto objects = loader.load<GLubyte>("test.obj");
        } else if (MODE == GRAPHIC_TEST) {
                //Img8b image = Img8b([path to a PNM image], PNM);
                Image<GLubyte> image = Image<GLubyte>(64, 64, 3, UV_GRID);
        
                GLuint Nom;
        
                glGenTextures(1, &Nom);               //Génère un n° de texture
                glBindTexture(GL_TEXTURE_2D, Nom);    //Sélectionne ce n°
                glTexImage2D (
                              GL_TEXTURE_2D,          //Type : texture 2D
                              0,                      //Mipmap : aucun
                              4,                      //Couleurs : 4
                              image.getWidth(),       //Largeur : 2
                              image.getHeight(),      //Hauteur : 2
                              0,                      //Largeur du bord : 0
                              image.getFormat(),      //Format : RGBA
                              GL_UNSIGNED_BYTE,       //Type des couleurs
                              image.getPixels()       //Addresse de l'image
                              );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
                drawCube();
        }
	refresh(mainWindow);
        
	SDL_ShowWindow(mainWindow);

	Uint32 last_time = SDL_GetTicks();
	Uint32 current_time,ellapsed_time;
	double angleZ(0), angleX(0);

	SDL_Event event;

	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
                                        exit(EXIT_SUCCESS);
                                        break;
				case SDL_KEYDOWN:
                                        if(event.key.keysym.sym == SDLK_q)
                                                exit(EXIT_SUCCESS);
			}
		}
		current_time	= SDL_GetTicks();
		ellapsed_time	= current_time - last_time;
		if (ellapsed_time < 10) SDL_Delay(10 - ellapsed_time);
		last_time		= current_time;


		angleZ = 0.04 * ellapsed_time;
		angleX = sqrt(0.01 * ellapsed_time);

		glRotated(angleX, 1, 0, 0);
		glRotated(angleZ, 0, 0, 1);
		drawCube();
		//objects[0].draw();
		refresh(mainWindow);
	}

	SDL_Quit();

	return 0;
}

/*
 * Initialize the needed libraries:
 * - SDL 2
 */

int initLibraries()
{
        if(!SDL_Init(SDL_INIT_VIDEO))
        {
                return true;
        } else {
                cerr << "ERROR: SDL initialisation:"
                     << SDL_GetError() << endl;
		return false;
        }
}

/*
 * Open a new window
 * Set windows icon
 * The window is not revealed
 */

SDL_Window* openWindow(SDL_Rect &windowRect, string &&title)
{
        SDL_Window *window = SDL_CreateWindow(
                                              "OpenGL",
                                              windowRect.x,
                                              windowRect.y,
                                              windowRect.w,
                                              windowRect.h,
                                              SDL_WINDOW_OPENGL |
                                                SDL_WINDOW_HIDDEN |
                                                SDL_WINDOW_RESIZABLE
                                              );
        
        SDL_SetWindowTitle(window, title.c_str());
        
        SDL_Surface *icon = SDL_LoadBMP("Resources/game_icon.bmp");
        SDL_SetWindowIcon(window, icon);
        
        SDL_GL_CreateContext(window);
        
        return window;
}
SDL_Window* openWindow(SDL_Rect &windowRect, string &title)
{
        SDL_Window *window = SDL_CreateWindow(
                                              "OpenGL",
                                              windowRect.x,
                                              windowRect.y,
                                              windowRect.w,
                                              windowRect.h,
                                              SDL_WINDOW_OPENGL |
                                              SDL_WINDOW_HIDDEN |
                                              SDL_WINDOW_RESIZABLE
                                              );
        
        SDL_SetWindowTitle(window, title.c_str());
        
        SDL_Surface *icon = SDL_LoadBMP("Resources/game_icon.bmp");
        SDL_SetWindowIcon(window, icon);
        
        SDL_GL_CreateContext(window);
        
        return window;
}

/*
 * Create an OpenGL context
 * Place Camera
 * Set the background color
 */

void initWindow(SDL_Window *window)
{
        int windowWidth, windowHeigth;
        SDL_GetWindowSize(window, &windowWidth, &windowHeigth);
        
	gluPerspective(60, (double) windowWidth / windowHeigth, 1, 1000);
	gluLookAt(3, 2, 2, 0, 0, 0, 0, 0, 1);
        
        glEnable(GL_DEPTH_TEST);        //Active le depth test
	glEnable(GL_TEXTURE_2D);        //Active le texturing
        
	glClearColor(0.16, 0.16, 0.16, 1);      //Change la couleur du fond
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
 * Draw a simple cube
 */

void drawCube()
{
	glBegin(GL_QUADS);
	glMatrixMode(GL_MODELVIEW);

	glColor3ub(255,255,255);
	glTexCoord2i(0,0); glVertex3d( 1, 1, 1);
	glTexCoord2i(0,1); glVertex3d( 1, 1,-1);
	glTexCoord2i(1,1); glVertex3d( 1,-1,-1);
	glTexCoord2i(1,0); glVertex3d( 1,-1, 1);

	glTexCoord2i(0,0); glVertex3d( 1,-1,-1);
	glTexCoord2i(0,1); glVertex3d( 1,-1, 1);
	glTexCoord2i(1,1); glVertex3d(-1,-1, 1);
	glTexCoord2i(1,0); glVertex3d(-1,-1,-1);

	glTexCoord2i(0,0); glVertex3d(-1,-1, 1);
	glTexCoord2i(0,1); glVertex3d(-1,-1,-1);
	glTexCoord2i(1,1); glVertex3d(-1, 1,-1);
	glTexCoord2i(1,0); glVertex3d(-1, 1, 1);

	glTexCoord2i(0,0); glVertex3d(-1, 1,-1);
	glTexCoord2i(0,1); glVertex3d(-1, 1, 1);
	glTexCoord2i(1,1); glVertex3d( 1, 1, 1);
	glTexCoord2i(1,0); glVertex3d( 1, 1,-1);

	glTexCoord2i(0,0); glVertex3d( 1, 1,-1);
	glTexCoord2i(0,1); glVertex3d(-1, 1,-1);
	glTexCoord2i(1,1); glVertex3d(-1,-1,-1);
	glTexCoord2i(1,0); glVertex3d( 1,-1,-1);

	glTexCoord2i(0,0); glVertex3d( 1, 1, 1);
	glTexCoord2i(0,1); glVertex3d(-1, 1, 1);
	glTexCoord2i(1,1); glVertex3d(-1,-1, 1);
	glTexCoord2i(1,0); glVertex3d( 1,-1, 1);

	glEnd();
}

/*
 * Refresh window
 */

void refresh(SDL_Window *window)
{
	glFlush();
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
}
