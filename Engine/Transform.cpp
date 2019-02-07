/*
LeoTamminen
Created 16/12/2018
*/

#include "Transform.hpp"

#include <iostream>

using namespace Engine;
using namespace Engine::Maths;

Matrix4f Transform::modelMatrixNew () const
{
    Matrix4f T = Matrix4f::translate(position);
    Matrix4f S = Matrix4f::scale(scale);

    return T * S;
}

Matrix4f Transform::inverseModelMatrix() const
{
    Matrix4f T = Matrix4f::translate(-position);
    Vector3f inverseScale ( 1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
    Matrix4f S = Matrix4f::scale(inverseScale);

    return S * T;
}