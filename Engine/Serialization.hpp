/*
Shophorn
Leo Tamminen
Created 07/02/2019
*/

#pragma once

#include <rapidjson/document.h>
#include <cassert>

namespace serialization
{
    using Value = rapidjson::Value;

    template <typename T>
    T deserialize(const Value & value);
}

