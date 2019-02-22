/*
LeoTamminen
Created 21/02/2019
*/

#pragma once

#include "Maths/Maths.hpp"

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