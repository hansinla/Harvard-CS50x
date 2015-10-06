/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false
 */
bool search(int value, int values[], int n)
{
    // check for valid n
    if (n <= 0)
    {
        return false;
    }
    
    // make sure array is sorted
    sort(values, n);
    
    int begin = 0;
    int end = n - 1;
    
    while ( begin <= end)
    {
        int mid = (begin + end) / 2;
        
        if (values[mid] < value)
        {
            begin = mid + 1;
        }
        else if (values[mid] > value )
        {
            end = mid - 1;
        }
        else
            return true;        
    }
    return false;
}

/**
 * Bubble Sorts array of n values
 */
void sort(int values[], int n)
{
    // O(n^2) sorting algorithm
    int maxVal;
    
    for (int i = 0 ; i < n - 1 ; i++)
    {
        for (int j = 0 ; j < n - i - 1 ; j++)
        {
            if (values[j] > values[j + 1])
            {
                maxVal = values[j];
                values[j] = values[j + 1];
                values[j + 1] = maxVal;
            }
        }
    }
    return;
}
