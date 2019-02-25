/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/
#include <rapidjson/document.h>
#include "StringOperations.hpp"

namespace Core
{
    namespace Serialization
    {
        using Value = rapidjson::Value;
        using namespace strOps;

        template <typename T>
        T deserialize(const Value & value);
    }
}

