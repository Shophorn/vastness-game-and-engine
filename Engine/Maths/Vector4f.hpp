/*
Shophorn Games
Leo Tamminen
Created 04/02/2019
*/

#pragma once

#include "Vector3f.hpp"

namespace Engine::Maths
{
    struct Vector4f
    {
        float values[4];

        Vector4f() : values{0, 0, 0, 0} {}

        explicit Vector4f(float f) : values{f, f, f, f} {}

        Vector4f(float _x, float _y, float _z, float _w) : values{_x, _y, _z, _w} {}

        Vector4f(Vector3f v, float w) : values{v.x, v.y, v.z, w} {}


        float & operator [] (int index);
        const float & operator [] (int index) const;
    };

    float dot(const Vector4f & lhs, const Vector4f & rhs);
}
