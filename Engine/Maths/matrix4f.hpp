/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

#include "vector3f.hpp"
#include "Vector4f.hpp"

namespace Core::Maths
{
    struct matrix4f
    {
        Vector4f columns [4];
        Vector4f &operator[] (int index)
        {
            return columns[index];
        }

        const Vector4f & operator[] (int index) const
        {
            return columns[index];
        }

        void setRow(int index, const Vector4f & r);
        Vector4f getRow(int index) const;

        void transpose();

        static matrix4f translate(vector3f translation);
        static matrix4f rotate(vector3f eulerRotation);
        static matrix4f scale(vector3f scale);

        Vector4f operator * (const Vector4f & v) const;
        matrix4f operator * (const matrix4f & rhs) const;

    };

}
