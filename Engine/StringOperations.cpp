/*
LeoTamminen
Created 20/01/2019
*/

#include <iostream>
#include "StringOperations.hpp"

bool strOps::equals(const char *a, const char *b)
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



bool strOps::compareExtension(const char *path, const char *extension)
{
    int stopIndex = -1;
    int index = 0;
    while (path[index] != 0)
    {
        if (path[index] == '.')
        {
            stopIndex = index;
        }
        index++;
    }


    // no extension found
    if (stopIndex < 0) return false;

    // Start comparing on position after finding stop
    int pathIndex = stopIndex + 1;
    int extensionIndex = 0;

    while (true)
    {
        if (path[pathIndex] != extension[extensionIndex])
        {
            return false;
        }

        if (path[pathIndex] == 0)
        {
            return true;
        }

        pathIndex++;
        extensionIndex++;
    }
}
bool strOps::compareExtension(std::string path, std::string extension)
{
    return strOps::compareExtension(path.c_str(), extension.c_str());
}