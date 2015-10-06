/********************************************
*
*       vigenere.c
*       Hans van Riet
*       cs50 pset2
*
* Gets a keyword from the command line and
* uses it to do a Vigenere encryption.
*********************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    // Check for valid input, otherwise bail with error message and return 1
    if (argc != 2)
    {
        printf("You need to enter a keyword.\n");
        return 1;
    }
    
    string keyword = argv[1];
    for (int i = 0, len = strlen(keyword) ; i < len ; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Illegal characters in keyword.\n");
            return 1;
        }
    }
    
    int keyLen = strlen(keyword);
    
    // Ask user for plaintext
    string plainText = GetString();
    
    // Rotate the plainText over 'key' number of positions
    // if the character is an alphabet character
    char keyChar;
    int counter = 0;
    for (int i = 0, len = strlen(plainText) ; i < len ; i++)
    {   
        keyChar = keyword[counter % keyLen];
        if (keyChar >= 'a' && keyChar <= 'z')
        {
            keyChar -= 'a';
        }
        else if (keyChar >= 'A' && keyChar <= 'Z')
        {
            keyChar -= 'A';
        }
        
        
        if (plainText[i] >= 'a' && plainText[i] <= 'z')
        {
            printf("%c",'a' + ((plainText[i] - 'a' + keyChar) % 26));
            counter++;
        }
        else if (plainText[i] >= 'A' && plainText[i] <= 'Z')
        {
            printf("%c",'A' + ((plainText[i] - 'A' + keyChar) % 26));
            counter++;
        }
        else
            printf("%c", plainText[i]);  
    }
    printf("\n");
    return 0;
}
