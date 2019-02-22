/*
LeoTamminen
Created 16/12/2018
*/

#include "Transform.hpp"

#include <iostream>

using namespace maths;

matrix4f Core::Transform::modelMatrixNew () const
{
    matrix4f T = matrix4f::translate(position);
    matrix4f S = matrix4f::scale(scale);

    return T * S;
}

matrix4f Core::Transform::inverseModelMatrix() const
{
    matrix4f T = matrix4f::translate(-position);
    vector3f inverseScale ( 1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
    matrix4f S = matrix4f::scale(inverseScale);

    return S * T;
}