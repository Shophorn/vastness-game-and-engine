/*
LeoTamminen
Created 31/01/2019
*/

#include "Matrix4f.hpp"
#include "OStreamOperators.hpp"

#include <iostream>

using namespace Engine::Maths;


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
        dot(v, Vector4f(m[0][0], m[1][0], m[2][0], m[3][0])),
        dot(v, Vector4f(m[0][1], m[1][1], m[2][1], m[3][1])),
        dot(v, Vector4f(m[0][2], m[1][2], m[2][2], m[3][2])),
        dot(v, Vector4f(m[0][3], m[1][3], m[2][3], m[3][3]))
    );
    return result;
}

Matrix4f Matrix4f::operator*(const Matrix4f & rhs) const
{
    const Matrix4f & lhs = *this;
    Matrix4f m;
    m[0][0] = dot(lhs.getRow(0), rhs[0]);
    m[1][0] = dot(lhs.getRow(0), rhs[1]);
    m[2][0] = dot(lhs.getRow(0), rhs[2]);
    m[3][0] = dot(lhs.getRow(0), rhs[3]);

    m[0][1] = dot(lhs.getRow(1), rhs[0]);
    m[1][1] = dot(lhs.getRow(1), rhs[1]);
    m[2][1] = dot(lhs.getRow(1), rhs[2]);
    m[3][1] = dot(lhs.getRow(1), rhs[3]);

    m[0][2] = dot(lhs.getRow(2), rhs[0]);
    m[1][2] = dot(lhs.getRow(2), rhs[1]);
    m[2][2] = dot(lhs.getRow(2), rhs[2]);
    m[3][2] = dot(lhs.getRow(2), rhs[3]);

    m[0][3] = dot(lhs.getRow(3), rhs[0]);
    m[1][3] = dot(lhs.getRow(3), rhs[1]);
    m[2][3] = dot(lhs.getRow(3), rhs[2]);
    m[3][3] = dot(lhs.getRow(3), rhs[3]);

    return m;
}

Vector4f Matrix4f::getRow(int index) const
{
    return Vector4f (
        columns[0][index],
        columns[1][index],
        columns[2][index],
        columns[3][index]
    );
}

void Matrix4f::setRow(int index, const Vector4f &r)
{
    columns[0][index] = r[0];
    columns[1][index] = r[1];
    columns[2][index] = r[2];
    columns[3][index] = r[3];
}

void Matrix4f::transpose()
{
    Vector4f r0 = getRow(0);
    Vector4f r1 = getRow(1);
    Vector4f r2 = getRow(2);
    Vector4f r3 = getRow(3);

    columns[0] = r0;
    columns[1] = r1;
    columns[2] = r2;
    columns[3] = r3;
}
