/********************************************
*
*       caesar.c
*       Hans van Riet
*       cs50 pset2
*
* Gets a key (int) from the command line and
* uses it to do a Caesar's encryption.
*********************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Check for valid input, otherwise bail with error message and return 1
    if (argc == 1 || atoi(argv[1]) < 1)
    {
        printf("You need to enter a non-negative integer.\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    
    // Ask user for plaintext
    string plainText = GetString();
    
    // Rotate the plainText over 'key' number of positions
    // if the character is an alphabet character
    for (int i = 0, len = strlen(plainText) ; i < len ; i++)
    {
        if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            printf("%c",'a' + ((plainText[i] - 'a' + key) % 26));
        }
        else if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            printf("%c",'A' + ((plainText[i] - 'A' + key) % 26));
        }
        else
            printf("%c", plainText[i]);  
    }
    printf("\n");
    return 0;
}
