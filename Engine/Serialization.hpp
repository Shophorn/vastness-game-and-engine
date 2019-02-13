/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/
#include <rapidjson/document.h>
#include "StringOperations.hpp"

namespace Engine
{
    namespace Serialization
    {
        using Value = rapidjson::Value;
        using namespace StringOperations;

        template <typename T>
        T deserialize(const Value & value);
    }
}

