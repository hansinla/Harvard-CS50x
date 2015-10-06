/********************************************
*
*       mario.c
*       Hans van Riet
*       cs50 pset1
*
*
*********************************************/

#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Variables
    int height;

    // Get user input for height
    do
    {
        printf("Height: ");
        height = GetInt();
    } 
    while(height < 0 || height > 23);

    // Print pyramid
    for (int i=0; i < height; i++)
    {
        for (int j = 1; j < height - i; j++)
        {
            printf("%s", " ");
        }
        for (int k = 0; k < i + 2; k++)
        {
            printf("%s", "#");
        }
        printf("\n");
    }
    

}

