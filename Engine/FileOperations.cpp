/*
LeoTamminen
Created 21/01/2019
*/

#include <string>
#include <sstream>
#include <fstream>

#include "FileOperations.hpp"

std::string fileOps::ReadFile(const std::string & path)
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

rapidjson::Document fileOps::ReadJson(const std::string & path)
{
    auto jsonFormat = fileOps::ReadFile(path);
    rapidjson::Document document;
    document.Parse(jsonFormat.c_str());
    return document;
}
