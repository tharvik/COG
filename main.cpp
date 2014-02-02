#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include <SDL2/SDL.h>

#include "opengl.h"

#include "Image.cpp"
#include "ObjLoader.h"
#include "Object.h"
#include "Camera.h"

int initLibraries();

SDL_Window* openWindow(SDL_Rect &windowRect, const std::string &title);

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
	Camera mainCamera = Camera(-3, 0, 0, 0, 0);

	std::vector<Object> objects;

	Image<GLubyte> img =
		Image<GLubyte>("Resources/Test files/mountain.png", PNG);

	if (argc == 2) {
		ObjLoader loader;
		objects = loader.load("Resources/Test files/mountain.obj");
		objects[0].setImage(img);
	} else {
		Image<GLubyte> img = Image<GLubyte>("Resources/test_GrayA.png");

		GLuint Nom;

		glGenTextures(1, &Nom);               //Génère un n° de texture
		glBindTexture(GL_TEXTURE_2D, Nom);    //Sélectionne ce n°
		glTexImage2D (
				  GL_TEXTURE_2D,          //Type : texture 2D
				  0,                      //Mipmap : aucun
				  4,                      //Couleurs : 4
				  img.getWidth(),         //Largeur : 2
				  img.getHeight(),        //Hauteur : 2
				  0,                      //Largeur du bord : 0
				  img.getFormat(),        //Format : RGBA
				  GL_UNSIGNED_BYTE,       //Type des couleurs
				  img.getPixels()         //Addresse de l'image
				  );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GL_NEAREST);

		drawCube();
	}
	refresh(mainWindow);

	SDL_ShowWindow(mainWindow);

	/*Uint32 last_time = SDL_GetTicks();
	Uint32 current_time,ellapsed_time;
	double angleZ(0), angleX(0);*/
	
	SDL_Event event;
	
	double a = 0, b = 0, c = 0;
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
					switch(event.key.keysym.sym)
					{
						case SDLK_q:
							exit(EXIT_SUCCESS);
							break;
						
						case SDLK_a:
							a -= 0.001;
							// mainCamera.rotateZ(-0.01);
							break;
						
						case SDLK_d:
							a += 0.001;
							// mainCamera.rotateZ(0.01);
							break;
						
						case SDLK_w:
							b -= 0.001;
							// mainCamera.rotateY(-0.01);
							break;
						
						case SDLK_s:
							b += 0.001;
							// mainCamera.rotateY(0.01);
							break;
						
						case SDLK_i:
							c += 0.005;
							// mainCamera.forwardBackward(0.05);
							break;
						
						case SDLK_k:
							c -= 0.005;
							// mainCamera.forwardBackward(-0.05);
							break;
					}
			}
		}
		/*
		 current_time	= SDL_GetTicks();
		 ellapsed_time	= current_time - last_time;
		 if (ellapsed_time < 10) SDL_Delay(10 - ellapsed_time);
		 last_time		= current_time;
		 */
		mainCamera.rotateZ(a);
		mainCamera.rotateY(b);
		mainCamera.forwardBackward(c);
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		gluPerspective(60, 800/450, 0.1, 1000);
		mainCamera.plant();
		objects[0].draw();
		
		glFlush();
		SDL_GL_SwapWindow(mainWindow);
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
                std::cerr << "ERROR: SDL initialisation:"
                          << SDL_GetError() << std::endl;
		return false;
        }

		//IMG_Init(IMG_INIT_PNG, IMG_INIT_JPG);
}

/*
 * Open a new window
 * Set windows icon
 * The window is not revealed
 */
SDL_Window* openWindow(SDL_Rect &windowRect, const std::string &title)
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

	gluPerspective(60, (double) windowWidth / windowHeigth, 0.1, 1000);


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
