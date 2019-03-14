/*
LeoTamminen
Created 21/01/2019
*/

#pragma once

#include <string>
#include <rapidjson/Document.h>

namespace fileOps
{
    std::string 		ReadFile(const std::string & path);


    using JsonDocument = rapidjson::Document;
    JsonDocument ReadJson(const std::string & path);
};


