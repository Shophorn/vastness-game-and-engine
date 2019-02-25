/*
Leo Tamminen
Created 20/01/2019
*/

#pragma once

#include <string>

namespace strOps
{
    bool equals(const char *a, const char *b);
    bool compareExtension(const char *path, const char *extension);
    bool compareExtension(std::string path, std::string extension);
};


