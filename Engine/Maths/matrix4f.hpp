/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

#include "vector3f.hpp"
#include "vector4f.hpp"

namespace maths
{
    struct matrix4f
    {
        vector4f columns [4];
        vector4f &operator[] (int index)
        {
            return columns[index];
        }

        const vector4f & operator[] (int index) const
        {
            return columns[index];
        }

        void setRow(int index, const vector4f & r);
        vector4f getRow(int index) const;

        void transpose();

        static matrix4f translate(vector3f translation);
        static matrix4f rotate(vector3f eulerRotation);
        static matrix4f scale(vector3f scale);

        vector4f operator * (const vector4f & v) const;
        matrix4f operator * (const matrix4f & rhs) const;

    };

}
