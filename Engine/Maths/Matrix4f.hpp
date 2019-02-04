/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

#include "Vector3f.hpp"
#include "Vector4f.hpp"

#include <iostream>

namespace Engine::Maths
{
    struct Matrix4f
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


        static Matrix4f translate(Vector3f translation);
        static Matrix4f rotate(Vector3f eulerRotation);
        static Matrix4f scale(Vector3f scale);

        Vector4f operator * (const Vector4f & v) const;
        Matrix4f operator * (const Matrix4f & rhs) const;

    };

}

    std::ostream & operator << (std::ostream & os, const Engine::Maths::Matrix4f & m);
