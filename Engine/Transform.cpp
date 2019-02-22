/*
LeoTamminen
Created 16/12/2018
*/

#include "Transform.hpp"

#include <iostream>

using namespace Core;
using namespace Core::Maths;

matrix4f Transform::modelMatrixNew () const
{
    matrix4f T = matrix4f::translate(position);
    matrix4f S = matrix4f::scale(scale);

    return T * S;
}

matrix4f Transform::inverseModelMatrix() const
{
    matrix4f T = matrix4f::translate(-position);
    vector3f inverseScale ( 1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
    matrix4f S = matrix4f::scale(inverseScale);

    return S * T;
}