// Copyright(c) 2019 Nick Klingensmith (@koujaku). All rights reserved.
//
// This work is licensed under the terms of the MIT license.
// For a copy of this license, see < https://opensource.org/licenses/MIT >

#ifndef __TGA_H__
#define __TGA_H__

#include <stdio.h>
#include <stdlib.h>

#include "rusty_ints.h"

struct Targa {
    u8* pixels;
    size_t width;
    size_t height;
};

// Writes an uncompressed 24 or 32 bit .tga image to the indicated file!
// filename: I'd recommended you add a '.tga' to the end of this filename.
// dataBGRA: A chunk of color data, one channel per byte, ordered as BGRA. Size should be width*height*dataChanels.
// dataChannels: The number of channels in the color data. Use 1 for grayscale, 3 for BGR, and 4 for BGRA.
// fileChannels: The number of color channels to write to file. Must be 3 for BGR, or 4 for BGRA. Does NOT need to match dataChannels.
bool tga_write(const char *filename, u32 width, u32 height, u8 *dataBGRA, u8 dataChannels=4, u8 fileChannels=3)
{
    
	FILE* fp = fopen(filename, "wb");
	if (fp == NULL) return false;

	// You can find details about TGA headers here: http://www.paulbourke.net/dataformats/tga/
	u8 header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0, (u8)(width%256), (u8)(width/256), (u8)(height%256), (u8)(height/256), (u8)(fileChannels*8), 0x20 };
	fwrite(&header, 18, 1, fp);

	for (u32 i = 0; i < width*height; i++)
	{
		for (u32 b = 0; b < fileChannels; b++)
		{
			fputc(dataBGRA[(i*dataChannels) + (b%dataChannels)], fp);
		}
	}
	fclose(fp);

    return true;
}

struct Targa tga_read(const char* filename) {
    struct Targa tga;
    tga.pixels = NULL;
    tga.width = tga.height = 0;

    FILE* fp = fopen(filename, "wb");
	if (fp == NULL) return tga;

	fclose(fp);

    return tga;
}

void tga_free(struct Targa* tga) {
    free(tga->pixels);
}

#endif // __TGA_H__
