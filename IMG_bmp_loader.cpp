/*
 This image loader is altered from the SDL2_image. The modifications has been
 done to avoid a SDL_surface creation.
 */

/*
 SDL_image:  An example image loading library for use with SDL
 Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>
 
 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 */

//
//  IMG_bmp.cpp
//  COG
//

#include <iostream>
#include "Image.h"

/* Compression encodings for BMP files */
#ifndef BI_RGB
#define BI_RGB       0
#define BI_RLE8      1
#define BI_RLE4      2
#define BI_BITFIELDS 3
#endif

template <class T>
void Image<T>::loadBMPimage(SDL_RWops *src)
{
	Uint32 pixelFormat;
	GLuint pitch;
	
	SDL_bool was_error;
    Sint64 fp_offset;
    int bmpPitch;
    int i, pad;
    Uint32 Rmask;
    Uint32 Gmask;
    Uint32 Bmask;
    Uint32 Amask;
    SDL_Palette *palette;
	
    GLubyte *bits;
    GLubyte *top, *end;
	
    SDL_bool topDown;
    int ExpandBMP;
    SDL_bool correctAlpha = SDL_FALSE;

    /* The Win32 BMP file header (14 bytes) */
    char   magic[2];
    Uint32 bfSize;
    Uint16 bfReserved1;
    Uint16 bfReserved2;
    Uint32 bfOffBits;

    /* The Win32 BITMAPINFOHEADER struct (40 bytes) */
    Uint32 biSize;
    Sint32 biWidth;
    Sint32 biHeight;
    Uint16 biPlanes;
    Uint16 biBitCount;
    Uint32 biCompression;
    Uint32 biSizeImage;
    Sint32 biXPelsPerMeter;
    Sint32 biYPelsPerMeter;
    Uint32 biClrUsed;
    Uint32 biClrImportant;

    /* Make sure we are passed a valid data source */
    was_error = SDL_FALSE;
    if (src == NULL) {
        was_error = SDL_TRUE;
        goto done;
    }

    /* Read in the BMP file header */
    fp_offset = SDL_RWtell(src);
    SDL_ClearError();
    if ( SDL_RWread(src, magic, 1, 2) != 2 ) {
        SDL_Error(SDL_EFREAD);
        was_error = SDL_TRUE;
        goto done;
    }
    if ( SDL_strncmp(magic, "BM", 2) != 0 ) {
        IMG_SetError("File is not a Windows BMP file");
        was_error = SDL_TRUE;
        goto done;
    }
    bfSize      = SDL_ReadLE32(src);
    bfReserved1 = SDL_ReadLE16(src);
    bfReserved2 = SDL_ReadLE16(src);
    bfOffBits   = SDL_ReadLE32(src);

    /* Read the Win32 BITMAPINFOHEADER */
    biSize      = SDL_ReadLE32(src);
    if ( biSize == 12 ) {
        biWidth     = (Uint32)SDL_ReadLE16(src);
        biHeight    = (Uint32)SDL_ReadLE16(src);
        biPlanes    = SDL_ReadLE16(src);
        biBitCount  = SDL_ReadLE16(src);
        biCompression   = BI_RGB;
        biSizeImage = 0;
        biXPelsPerMeter = 0;
        biYPelsPerMeter = 0;
        biClrUsed   = 0;
        biClrImportant  = 0;
    } else {
        biWidth     = SDL_ReadLE32(src);
        biHeight    = SDL_ReadLE32(src);
        biPlanes    = SDL_ReadLE16(src);
        biBitCount  = SDL_ReadLE16(src);
        biCompression   = SDL_ReadLE32(src);
        biSizeImage = SDL_ReadLE32(src);
        biXPelsPerMeter = SDL_ReadLE32(src);
        biYPelsPerMeter = SDL_ReadLE32(src);
        biClrUsed   = SDL_ReadLE32(src);
        biClrImportant  = SDL_ReadLE32(src);
    }
    if (biHeight < 0) {
        topDown = SDL_TRUE;
        biHeight = -biHeight;
    } else {
        topDown = SDL_FALSE;
    }

    /* Check for read error */
    if ( strcmp(SDL_GetError(), "") != 0 ) {
        was_error = SDL_TRUE;
        goto done;
    }

    /* Expand 1 and 4 bit bitmaps to 8 bits per pixel */
    switch (biBitCount) {
        case 1:
        case 4:
            ExpandBMP = biBitCount;
            biBitCount = 8;
            break;
        default:
            ExpandBMP = 0;
            break;
    }

    /* RLE4 and RLE8 BMP compression is supported */
    Rmask = Gmask = Bmask = Amask = 0;
    switch (biCompression) {
        case BI_RGB:
            /* If there are no masks, use the defaults */
            if ( bfOffBits == (14+biSize) ) {
                /* Default values for the BMP format */
                switch (biBitCount) {
                    case 15:
                    case 16:
                        Rmask = 0x7C00;
                        Gmask = 0x03E0;
                        Bmask = 0x001F;
                        break;
                    case 24:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                        Rmask = 0x000000FF;
                        Gmask = 0x0000FF00;
                        Bmask = 0x00FF0000;
#else
                        Rmask = 0x00FF0000;
                        Gmask = 0x0000FF00;
                        Bmask = 0x000000FF;
#endif
                        break;
                    case 32:
                        /* We don't know if this has alpha channel or not */
                        correctAlpha = SDL_TRUE;
                        Amask = 0xFF000000;
                        Rmask = 0x00FF0000;
                        Gmask = 0x0000FF00;
                        Bmask = 0x000000FF;
                        break;
                    default:
                        break;
                }
                break;
            }
            /* Fall through -- read the RGB masks */

        default:
            switch (biBitCount) {
                case 15:
                case 16:
                    Rmask = SDL_ReadLE32(src);
                    Gmask = SDL_ReadLE32(src);
                    Bmask = SDL_ReadLE32(src);
                    break;
                case 32:
                    Rmask = SDL_ReadLE32(src);
                    Gmask = SDL_ReadLE32(src);
                    Bmask = SDL_ReadLE32(src);
                    Amask = SDL_ReadLE32(src);
                    break;
                default:
                    break;
            }
            break;
    }
	
	w = biWidth;
	h = biHeight;
	d = biBitCount / 8;
	pitch = w * d;
	
	pixels = (T*) calloc(h * pitch, sizeof(T*));
		
	// Create format if pixelFormat indexed
	palette = NULL;
	if (SDL_ISPIXELFORMAT_INDEXED(pixelFormat)) {
		pixelFormat = SDL_MasksToPixelFormatEnum(biBitCount, Rmask, Gmask, Bmask, Amask);
		
		if (pixelFormat == SDL_PIXELFORMAT_UNKNOWN) {
			SDL_SetError("Unknown pixel format");
			goto done;
		}
		
		// Create palette
		palette = SDL_AllocPalette(1 << biBitCount);
				
		if (palette->ncolors == 2) {
			/* Create a black and white bitmap palette */
			palette->colors[0].r = 0xFF;
			palette->colors[0].g = 0xFF;
			palette->colors[0].b = 0xFF;
			palette->colors[1].r = 0x00;
			palette->colors[1].g = 0x00;
			palette->colors[1].b = 0x00;
		}
	}
	
	std::cout << w << "x" << h << "x" << d << endl; 
			
    /* Load the palette, if any */
    if (palette != NULL) {
        if ( SDL_RWseek(src, fp_offset+14+biSize, RW_SEEK_SET) < 0 ) {
            SDL_Error(SDL_EFSEEK);
            was_error = SDL_TRUE;
            goto done;
        }

        /*
        | guich: always use 1<<bpp b/c some bitmaps can bring wrong information
        | for colorsUsed
        */
        /* if ( biClrUsed == 0 ) {  */
        biClrUsed = 1 << biBitCount;
        /* } */
        if ( biSize == 12 ) {
            for ( i = 0; i < (int)biClrUsed; ++i ) {
                SDL_RWread(src, &palette->colors[i].b, 1, 1);
                SDL_RWread(src, &palette->colors[i].g, 1, 1);
                SDL_RWread(src, &palette->colors[i].r, 1, 1);
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        } else {
            for ( i = 0; i < (int)biClrUsed; ++i ) {
                SDL_RWread(src, &palette->colors[i].b, 1, 1);
                SDL_RWread(src, &palette->colors[i].g, 1, 1);
                SDL_RWread(src, &palette->colors[i].r, 1, 1);
                SDL_RWread(src, &palette->colors[i].a, 1, 1);

                /* According to Microsoft documentation, the fourth element
                   is reserved and must be zero, so we shouldn't treat it as
                   alpha.
                */
                palette->colors[i].a = SDL_ALPHA_OPAQUE;
            }
        }
        palette->ncolors = biClrUsed;
    }

    /* Note that the bmp image is upside down */
    if ( SDL_RWseek(src, fp_offset+bfOffBits, RW_SEEK_SET) < 0 ) {
        SDL_Error(SDL_EFSEEK);
        was_error = SDL_TRUE;
        goto done;
    }
    if ((biCompression == BI_RLE4) || (biCompression == BI_RLE8)) {
        was_error = (SDL_bool) readRlePixels(src, biCompression == BI_RLE8);
        if (was_error) IMG_SetError("Error reading from BMP");
        goto done;
    }
    top = (GLubyte *) pixels;
    end = (GLubyte *) pixels + (h * pitch);
    switch (ExpandBMP) {
        case 1:
            bmpPitch = (biWidth + 7) >> 3;
            pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
            break;
        case 4:
            bmpPitch = (biWidth + 1) >> 1;
            pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
            break;
        default:
            pad  = ((pitch%4) ?
                    (4-(pitch%4)) : 0);
            break;
    }
    if ( topDown ) {
        bits = top;
    } else {
        bits = end - pitch;
    }
    while ( bits >= top && bits < end ) {
        switch (ExpandBMP) {
            case 1:
            case 4: {
            Uint8 pixel = 0;
            int   shift = (8-ExpandBMP);
            for ( i=0; i < w; ++i ) {
                if ( i%(8/ExpandBMP) == 0 ) {
                    if ( !SDL_RWread(src, &pixel, 1, 1) ) {
                        IMG_SetError("Error reading from BMP");
                        was_error = SDL_TRUE;
                        goto done;
                    }
                }
                *(bits+i) = (pixel>>shift);
                pixel <<= ExpandBMP;
            } }
            break;

            default:
            if ( SDL_RWread(src, bits, 1, pitch) != pitch ) {
                SDL_Error(SDL_EFREAD);
                was_error = SDL_TRUE;
                goto done;
            }
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            /* Byte-swap the pixels if needed. Note that the 24bpp
               case has already been taken care of above. */
            switch(biBitCount) {
                case 15:
                case 16: {
                    Uint16 *pix = (Uint16 *)bits;
                    for(i = 0; i < w; i++)
                        pix[i] = SDL_Swap16(pix[i]);
                    break;
                }

                case 32: {
                    Uint32 *pix = (Uint32 *)bits;
                    for(i = 0; i < w; i++)
                        pix[i] = SDL_Swap32(pix[i]);
                    break;
                }
            }
#endif
            break;
        }
        /* Skip padding bytes, ugh */
        if ( pad ) {
            Uint8 padbyte;
            for ( i=0; i<pad; ++i ) {
                SDL_RWread(src, &padbyte, 1, 1);
            }
        }
        if ( topDown ) {
            bits += pitch;
        } else {
            bits -= pitch;
        }
    }
    if (correctAlpha) {
        CorrectAlphaChannel();
    }
done:
    if ( was_error ) {
        if ( src ) {
            SDL_RWseek(src, fp_offset, RW_SEEK_SET);
        }
    }
    if (src) {
        SDL_RWclose(src);
    }
}

template <class T>
int Image<T>::readRlePixels(SDL_RWops * src, int isRle8)
{
    /*
		A bmp image is upside down.
    */
    int pitch = w * d;
    int height = h;
    Uint8 *start;
	start = (Uint8 *) pixels;
    Uint8 *end = start + (height*pitch);
    Uint8 *bits = end-pitch, *spot;
    int ofs = 0;
    Uint8 ch;
    Uint8 needsPad;

#define COPY_PIXEL(x)   spot = &bits[ofs++]; if(spot >= start && spot < end) *spot = (x)

    for (;;) {
        if ( !SDL_RWread(src, &ch, 1, 1) ) return 1;
        /*
        | encoded mode starts with a run length, and then a byte
        | with two colour indexes to alternate between for the run
        */
        if ( ch ) {
            Uint8 pixel;
            if ( !SDL_RWread(src, &pixel, 1, 1) ) return 1;
            if ( isRle8 ) {                 /* 256-color bitmap, compressed */
                do {
                    COPY_PIXEL(pixel);
                } while (--ch);
            } else {                         /* 16-color bitmap, compressed */
                Uint8 pixel0 = pixel >> 4;
                Uint8 pixel1 = pixel & 0x0F;
                for (;;) {
                    COPY_PIXEL(pixel0); /* even count, high nibble */
                    if (!--ch) break;
                    COPY_PIXEL(pixel1); /* odd count, low nibble */
                    if (!--ch) break;
                }
            }
        } else {
            /*
            | A leading zero is an escape; it may signal the end of the bitmap,
            | a cursor move, or some absolute data.
            | zero tag may be absolute mode or an escape
            */
            if ( !SDL_RWread(src, &ch, 1, 1) ) return 1;
            switch (ch) {
            case 0:                         /* end of line */
                ofs = 0;
                bits -= pitch;               /* go to previous */
                break;
            case 1:                         /* end of bitmap */
                return 0;                    /* success! */
            case 2:                         /* delta */
                if ( !SDL_RWread(src, &ch, 1, 1) ) return 1;
                ofs += ch;
                if ( !SDL_RWread(src, &ch, 1, 1) ) return 1;
                bits -= (ch * pitch);
                break;
            default:                        /* no compression */
                if (isRle8) {
                    needsPad = ( ch & 1 );
                    do {
                        Uint8 pixel;
                        if ( !SDL_RWread(src, &pixel, 1, 1) ) return 1;
                        COPY_PIXEL(pixel);
                    } while (--ch);
                } else {
                    needsPad = ( ((ch+1)>>1) & 1 ); /* (ch+1)>>1: bytes size */
                    for (;;) {
                        Uint8 pixel;
                        if ( !SDL_RWread(src, &pixel, 1, 1) ) return 1;
                        COPY_PIXEL(pixel >> 4);
                        if (!--ch) break;
                        COPY_PIXEL(pixel & 0x0F);
                        if (!--ch) break;
                    }
                }
                /* pad at even boundary */
                if ( needsPad && !SDL_RWread(src, &ch, 1, 1) ) return 1;
                break;
            }
        }
    }
}

template <class T>
void Image<T>::CorrectAlphaChannel()
{
	GLuint pitch = w * d;

    /* Check to see if there is any alpha channel data */
    SDL_bool hasAlpha = SDL_FALSE;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    int alphaChannelOffset = 0;
#else
    int alphaChannelOffset = 3;
#endif
    Uint8 *alpha = ((GLubyte*) pixels) + alphaChannelOffset;
    Uint8 *end = alpha + h * pitch;

    while (alpha < end) {
        if (*alpha != 0) {
            hasAlpha = SDL_TRUE;
            break;
        }
        alpha += 4;
    }

    if (!hasAlpha) {
        alpha = ((Uint8*) pixels) + alphaChannelOffset;
        while (alpha < end) {
            *alpha = SDL_ALPHA_OPAQUE;
            alpha += 4;
        }
    }
}
