/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

namespace Engine::Maths
{
    struct Vector3f
    {
        float x, y, z;

        Vector3f() : x(0), y(0), z(0) {}
        Vector3f(float value) : x(value), y(value), z(value) {}
        Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        static const Vector3f down;
        static const Vector3f up;
        static const Vector3f left;
        static const Vector3f right;
        static const Vector3f back;
        static const Vector3f forward;

        Vector3f & operator += (const Vector3f & rhs);
        Vector3f & operator -= (const Vector3f & rhs);

        Vector3f operator + (const Vector3f & rhs);
        Vector3f operator - (const Vector3f & rhs);

        Vector3f & operator *= (float f);
        Vector3f & operator /= (float f);

        Vector3f operator * (float f) const;
        Vector3f operator / (float f) const;

        Vector3f operator - () const;

    };

    Vector3f normalize(const Vector3f & v);
    float dot(const Vector3f & lhs, const Vector3f & rhs);
    Vector3f cross(const Vector3f & lhs, const Vector3f & rhs);
    float magnitude(const Vector3f &v);

}
