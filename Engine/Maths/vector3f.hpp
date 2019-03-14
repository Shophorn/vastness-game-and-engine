/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

// #include "Quaternion.hpp"

namespace maths
{
    struct vector3f
    {
        float x, y, z;

        vector3f() : x(0), y(0), z(0) {}
        explicit vector3f(float value) : x(value), y(value), z(value) {}
        vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

        static const vector3f down;
        static const vector3f up;
        static const vector3f left;
        static const vector3f right;
        static const vector3f back;
        static const vector3f forward;

        vector3f & operator += (const vector3f & rhs);
        vector3f & operator -= (const vector3f & rhs);

        vector3f operator + (const vector3f & rhs) const;
        vector3f operator - (const vector3f & rhs) const;

        vector3f & operator *= (float f);
        vector3f & operator /= (float f);

        vector3f operator * (float f) const;
        vector3f operator / (float f) const;

        vector3f operator - () const;

        bool operator == (const vector3f & other);
    };

    inline vector3f operator * (float f, vector3f v) { return v * f; }
    inline vector3f operator / (float f, vector3f v) { return v / f; }


    vector3f normalize(vector3f v);
    float dot(const vector3f & lhs, const vector3f & rhs);
    vector3f cross(const vector3f & lhs, const vector3f & rhs);

    float angle(const vector3f & lhs, const vector3f & rhs);
    float signedAngle(const vector3f & lhs, const vector3f & rhs, const vector3f & up = vector3f::up);
    float magnitude(const vector3f & v);
    float sqrMagnitude(const vector3f & v);
    float sqrDistance(const vector3f & lhs, const vector3f & rhs);

}
