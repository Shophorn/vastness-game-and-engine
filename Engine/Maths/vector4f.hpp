/*
Shophorn Games
Leo Tamminen
Created 04/02/2019
*/

#pragma once

#include "vector3f.hpp"

namespace maths
{
    struct vector4f
    {
        float values[4];

        vector4f() : values{0, 0, 0, 0} {}
        explicit vector4f(float f) : values{f, f, f, f} {}
        vector4f(float _x, float _y, float _z, float _w) : values{_x, _y, _z, _w} {}
        vector4f(vector3f v, float w) : values{v.x, v.y, v.z, w} {}

        float & operator [] (int index);
        const float & operator [] (int index) const;
    };

    float dot(const vector4f & lhs, const vector4f & rhs);
}
