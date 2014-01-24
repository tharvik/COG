#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <SDL2/SDL.h>

#include "opengl.h"

#include "Image.cpp"
#include "ObjLoader.h"

#define WINDOWWIDTH  800
#define WINDOWHEIGTH 450

SDL_Window* initGraphic();

void drawCube();
void refresh(SDL_Window *window);

int main(int argc, char *argv[])
{
	//Img8b image = Img8b("/Users/Vianney/Xcode/Cplusplus OpenGL/Cplusplus OpenGL/test_ASCII_Gray.pgm", PNM);
	Image<GLubyte> image = Image<GLubyte>(64, 64, 3, UV_GRID);
	//obj_loader loader;
	//auto objects = loader.load("test (UVs on).obj");
	//auto objects = loader.load("test (UVs off).obj");

	SDL_Window *window = initGraphic();

	GLuint Nom;

	glGenTextures(1 , &Nom);		//Génère un n° de texture
	glBindTexture(GL_TEXTURE_2D, Nom);	//Sélectionne ce n°
	glTexImage2D (
			GL_TEXTURE_2D,	//Type : texture 2D
			0,	//Mipmap : aucun
			4,	//Couleurs : 4
			image.getWidth(),	//Largeur : 2
			image.getHeight(),	//Hauteur : 2
			0,	//Largeur du bord : 0
			image.getFormat(),	//Format : RGBA
			GL_UNSIGNED_BYTE,	//Type des couleurs
			image.getPixels()//Addresse de l'image
		     );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	drawCube();
	refresh(window);

	SDL_ShowWindow(window);

	Uint32 last_time = SDL_GetTicks();
	Uint32 current_time,ellapsed_time;
	double angleZ(0), angleX(0);

	SDL_Event event;

	for (;;)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					exit(EXIT_SUCCESS);
					break;
				case SDL_KEYDOWN: if(event.key.keysym.sym == SDLK_q)
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
		refresh(window);
	}

	SDL_Quit(
		);

	return 0;
}

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

void refresh(SDL_Window *window)
{
	glFlush();
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
}

SDL_Window* initGraphic()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow(
			"OpenGL",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOWWIDTH,
			WINDOWHEIGTH,
			SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

	SDL_GL_CreateContext(window);

	gluPerspective(60, (double) WINDOWWIDTH / WINDOWHEIGTH, 1, 1000);
	gluLookAt(3, 2, 2, 0, 0, 0, 0, 0, 1);

	glClearColor(.16,.16,.16,1);	//Change la couleur du fond
	glEnable(GL_DEPTH_TEST);	//Active le depth test
	glEnable(GL_TEXTURE_2D);	//Active le texturing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return window;

}
