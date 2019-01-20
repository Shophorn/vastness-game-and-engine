/*
LeoTamminen
Created 20/01/2019
*/

#include "StringOperations.hpp"

bool StringOperations::Equals(const char *a, const char *b)
{
    int index = 0;
    while(true)
    {
        // Not same -> false
        if (a[index] != b [index])
        {
            return false;
        }

        // These are same at this point, only check if a is 0
        if (a[index] == 0)
        {
            return true;
        }

        index++;
    }
}
