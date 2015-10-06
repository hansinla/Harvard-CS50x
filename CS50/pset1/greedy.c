/********************************************
*
*       greedy.c
*       Hans van Riet
*       cs50 pset1
*
*
*********************************************/
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Variables
    float change;
    int numQuarters = 0, numDimes = 0, numNickels = 0, numCents = 0;
    
    // Get correct user input for amount of change to owe
    do
    {
        printf("How much change do I owe? ");
        change = GetFloat();
    }
    while (change < 0);
    
    // Convert input from float to int centsls
    
    numCents = (int) round(100 * change);
    
    // Calculate number of coins per denomination
    numQuarters = numCents / 25;
    numCents = numCents - (25 * numQuarters);
    numDimes = numCents / 10;
    numCents = numCents - (10 * numDimes);
    numNickels = numCents / 5;
    numCents = numCents - (5 * numNickels);
    
    // Print output per requirements.
    printf("%d\n", numQuarters + numDimes + numNickels + numCents);
}
