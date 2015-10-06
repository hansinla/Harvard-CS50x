/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 * Recovers JPEGs from a forensic image.
 *
 * Hans van Riet 2014
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

bool testHeader(char* buffer);

int main(void)
{
    // Open infile
    char* infile = "card.raw";
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    char buffer[BLOCK_SIZE];
    char filename[8];
    int fcounter = 0;
    int readSize = 0;
    
    
    while (fread(&buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        bool fileFound = false;
        if (testHeader(buffer))
        {
            sprintf(filename, "%.3d.jpg", fcounter);
            FILE* outptr = fopen(filename, "w");
            fwrite(&buffer, BLOCK_SIZE, 1, outptr);
            while (!fileFound)
            {
                readSize = fread(&buffer, BLOCK_SIZE, 1, inptr);
                if (feof(inptr))
                {
                    fwrite(&buffer, readSize, 1, outptr);
                    fclose(inptr);
                    fclose(outptr);
                    return 0;
                }
                if (!testHeader(buffer))
                {
                    fwrite(&buffer, BLOCK_SIZE, 1, outptr);
                }
                else
                {
                    fclose(outptr);
                    fcounter++;
                    fseek(inptr, -BLOCK_SIZE, SEEK_CUR);
                    fileFound = true;
                }
            }
        }  
    }
    fclose(inptr);
    return 0; 
}

bool testHeader(char* buffer)
{
    if (buffer[0] == (char)0xff && buffer[1] == (char)0xd8
        && buffer[2] == (char)0xff &&
        (buffer[3] == (char)0xe0 || buffer[3] == (char)0xe1))
        {
            return true;
        }
    return false;
}
