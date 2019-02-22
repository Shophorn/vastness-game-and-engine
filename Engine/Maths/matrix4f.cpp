/*
LeoTamminen
Created 31/01/2019
*/

#include "matrix4f.hpp"
#include "OStreamOperators.hpp"

#include <iostream>

using namespace maths;

matrix4f matrix4f::scale(vector3f scale)
{
    matrix4f S;
    S[0] = vector4f(scale.x, 0, 0, 0);
    S[1] = vector4f(0, scale.y, 0, 0);
    S[2] = vector4f(0, 0, scale.z, 0);
    S[3] = vector4f(0, 0, 0, 1);

    return S;
}

matrix4f matrix4f::rotate(vector3f eulerRotation)
{
    matrix4f R;
    R[0] = vector4f(1, 0, 0, 0);
    R[1] = vector4f(0, 1, 0, 0);
    R[2] = vector4f(0, 0, 1, 0);
    R[3] = vector4f(0, 0, 0, 1);

    return R;
}

matrix4f matrix4f::translate(vector3f translation)
{
    matrix4f T;
    T[0] = vector4f(1, 0, 0, 0);
    T[1] = vector4f(0, 1, 0, 0);
    T[2] = vector4f(0, 0, 1, 0);
    T[3] = vector4f(translation, 1.0f);

    return T;
}

vector4f matrix4f::operator*(const vector4f & v) const
{
    const matrix4f & m = *this;
    vector4f result
    (
        dot(v, vector4f(m[0][0], m[1][0], m[2][0], m[3][0])),
        dot(v, vector4f(m[0][1], m[1][1], m[2][1], m[3][1])),
        dot(v, vector4f(m[0][2], m[1][2], m[2][2], m[3][2])),
        dot(v, vector4f(m[0][3], m[1][3], m[2][3], m[3][3]))
    );
    return result;
}

matrix4f matrix4f::operator*(const matrix4f & rhs) const
{
    const matrix4f & lhs = *this;
    matrix4f m;
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

vector4f matrix4f::getRow(int index) const
{
    return vector4f (
        columns[0][index],
        columns[1][index],
        columns[2][index],
        columns[3][index]
    );
}

void matrix4f::setRow(int index, const vector4f &r)
{
    columns[0][index] = r[0];
    columns[1][index] = r[1];
    columns[2][index] = r[2];
    columns[3][index] = r[3];
}

void matrix4f::transpose()
{
    vector4f r0 = getRow(0);
    vector4f r1 = getRow(1);
    vector4f r2 = getRow(2);
    vector4f r3 = getRow(3);

    columns[0] = r0;
    columns[1] = r1;
    columns[2] = r2;
    columns[3] = r3;
}
