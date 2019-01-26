/*
LeoTamminen
Created 21/01/2019
*/

#pragma once

#include <fstream>
#include <string>

#include <rapidjson/Document.h>

namespace FileOperations
{
    const char * ReadFile(const char *path);

    rapidjson::Document ReadJson(const char * path);
};


