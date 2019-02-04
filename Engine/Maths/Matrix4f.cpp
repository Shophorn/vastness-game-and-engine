/*
LeoTamminen
Created 31/01/2019
*/

#include "Matrix4f.hpp"

#include <iomanip>

using namespace Engine::Maths;

std::ostream & operator << (std::ostream & os, const Matrix4f & m)
{
    os << std::setprecision(2);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            os << std::setw(5) << m[i][j] << "\t";
        }
        os << "\n";
    }
    return os;
}

Matrix4f Matrix4f::scale(Vector3f scale)
{
    Matrix4f S;
    S[0] = Vector4f(scale.x, 0, 0, 0);
    S[1] = Vector4f(0, scale.y, 0, 0);
    S[2] = Vector4f(0, 0, scale.z, 0);
    S[3] = Vector4f(0, 0, 0, 1);

    return S;
}

Matrix4f Matrix4f::rotate(Vector3f eulerRotation)
{
    Matrix4f R;
    R[0] = Vector4f(1, 0, 0, 0);
    R[1] = Vector4f(0, 1, 0, 0);
    R[2] = Vector4f(0, 0, 1, 0);
    R[3] = Vector4f(0, 0, 0, 1);

    return R;
}

Matrix4f Matrix4f::translate(Vector3f translation)
{
    Matrix4f T;
    T[0] = Vector4f(1, 0, 0, 0);
    T[1] = Vector4f(0, 1, 0, 0);
    T[2] = Vector4f(0, 0, 1, 0);
    T[3] = Vector4f(translation, 1.0f);

    return T;
}

Vector4f Matrix4f::operator*(const Vector4f & v) const
{
    const Matrix4f & m = *this;
    Vector4f result
    (
        dot(v, m[0]),
        dot(v, m[1]),
        dot(v, m[2]),
        dot(v, m[3])
    );
    return result;
}

Matrix4f Matrix4f::operator*(const Matrix4f & rhs) const
{
    const Matrix4f & lhs = *this;
    Matrix4f result;
    result[0] = lhs * rhs[0];
    result[1] = lhs * rhs[1];
    result[2] = lhs * rhs[2];
    result[3] = lhs * rhs[3];
    return result;
}
