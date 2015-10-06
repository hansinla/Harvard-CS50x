/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Scale a BMP by a factor and outputs a new file.
 *
 * Hans van Riet 2014
 *
 */  
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }
    
    int scaleFactor = atoi(argv[1]);
    
    if (scaleFactor <= 0)
    {
        printf("The scale factor must be an integer > 0.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int oldpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER outbf;
    
    outbf.bfType = bf.bfType;
    outbf.bfReserved1 = bf.bfReserved1; 
    outbf.bfReserved2 = bf.bfReserved2; 
    outbf.bfOffBits = bf.bfOffBits; 
  
    // outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER outbi;
    
    outbi.biSize = bi.biSize; 
    outbi.biWidth = bi.biWidth * scaleFactor;
    outbi.biHeight = bi.biHeight * scaleFactor;
    outbi.biPlanes = bi.biPlanes; 
    outbi.biBitCount = bi.biBitCount; 
    outbi.biCompression = bi.biCompression; 
    
    outbi.biXPelsPerMeter = bi.biXPelsPerMeter; 
    outbi.biYPelsPerMeter = bi.biYPelsPerMeter; 
    outbi.biClrUsed = bi.biClrUsed; 
    outbi.biClrImportant = bi.biClrImportant; 
        
    // determine padding for scanlines
    int newpadding =  (4 - (outbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    outbf.bfSize = 54 + abs(outbi.biHeight) * outbi.biWidth * 3 + abs(outbi.biHeight) * newpadding;
    outbi.biSizeImage = abs(outbi.biHeight) * outbi.biWidth * 3 + abs(outbi.biHeight) * newpadding;

    // write outfile's BITMAPFILEHEADER
    fwrite(&outbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int counter = 0;
        // repeat scanline per the scalefactor
        for (int m = 0 ; m < scaleFactor ; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write scale factor as many pixels to outfile
                for (int l = 0 ; l < scaleFactor ; l++)
                { 
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // write padding
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
            counter++;
            // reset the inptr to beginning of line
            if (counter < scaleFactor)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);
    }

    // close infile & outfile
    fclose(inptr); 
    fclose(outptr);

    return 0;
}
