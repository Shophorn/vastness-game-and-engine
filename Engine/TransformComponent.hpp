/*
LeoTamminen
Created 21/02/2019
*/

#pragma once

#include "Maths/Maths.hpp"
#include "Serialization.hpp"
#include "DEBUG.hpp"

struct transform
{
    vector3f position { 0 };
    vector3f rotation { 0 };
    vector3f scale { 1 };
};

inline matrix4f modelMatrix(const transform & tr)
{
    matrix4f T = matrix4f::translate(tr.position);
    matrix4f S = matrix4f::scale(tr.scale);

    return T * S;
}

inline matrix4f inverseModelMatrix(const transform & tr)
{
    matrix4f IT = matrix4f::translate(-tr.position);

    vector3f inverseScale ( 1.0f/ tr.scale.x, 1.0f / tr.scale.y, 1.0f / tr.scale.z);
    matrix4f IS = matrix4f::scale(inverseScale);

    return IS * IT;
}

namespace serialization
{
    template <>
    inline transform deserialize<transform>(const Value & value)
    {
        transform result;
        if (value.HasMember("position"))
            result.position = deserialize<vector3f>(value["position"]);

        if (value.HasMember("rotation"))
            result.rotation = deserialize<vector3f>(value["rotation"]);

        if (value.HasMember("scale"))
            result.scale = deserialize<vector3f>(value["scale"]);

        return result;
    }
}