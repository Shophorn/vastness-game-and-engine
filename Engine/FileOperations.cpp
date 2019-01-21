/*
LeoTamminen
Created 21/01/2019
*/

#include "FileOperations.hpp"

const char *FileOperations::ReadFile(const char *path)
{
    using namespace std;

    ifstream file (path, ios::in | ios::binary);
    if (!file.good()) return nullptr;

    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);

    char * source = new char [length + 1];

    file.read(source, length);

    source[length] = 0;

    return source;
}
