/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/
#include <rapidjson/document.h>

namespace Engine
{
    namespace Serialization
    {
        using Value = rapidjson::Value;

        template <typename T>
        T deserialize(const Value & value);
    }
}

