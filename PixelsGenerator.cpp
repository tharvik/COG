#include "PixelsGenerator.h"

GLubyte* generateRandomPixels(const GLushort width, const GLushort height,
		const GLubyte depth)
{
	srand((int) time(NULL));

	GLubyte* pixels = (GLubyte*) calloc(width * height * depth, sizeof(GLubyte));
	
	for (GLuint i = 0; i < (GLuint) width * height * depth; i++)
		pixels[i] = rand() % (GLubyte) (ceil(pow(2, 8 * sizeof(GLubyte))) - 1);

	return pixels;
}

GLubyte* generateUVgrid(const GLushort width, const GLushort height,
		const GLubyte depth)
{
	GLubyte* pixels = (GLubyte*) calloc(width * height * depth, sizeof(GLubyte));
	
	GLuint pixelID = 0;
	
	for (GLushort y = 0; y < height; y++) {
		for (GLushort x = 0; x < width; x++) {
			for (GLubyte d = 0; d < depth; d++) {
				
				pixelID = y * width * depth + x * depth + d;
				
				if(!((y+7 )%16+(x+7 )%16) || !((y+7 )%16+(x+10)%16)
				|| !((y+10)%16+(x+7 )%16) || !((y+10)%16+(x+10)%16))
				{
					if ((y/16 + x/16) % 2)
						pixels[pixelID] = rand() % (GLubyte) (ceil(pow(2, 8 * sizeof(GLubyte))/3) - 1)
						+ ceil(pow(2, 8 * sizeof(GLubyte))/3*2);
					
					else
						pixels[pixelID] = rand() % (GLubyte) (ceil(pow(2, 8 * sizeof(GLubyte))/1.5) - 1);
				}
				
				else pixels[pixelID] = ((y/16 + x/16) % 2) ? 0x42 : 0xaa;
			}
		}
	}
	
	return pixels;
}
