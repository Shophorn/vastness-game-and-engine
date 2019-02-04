/*
Shophorn Games
Leo Tamminen
Created 31/01/2019
*/

#pragma once

#include "Vector3f.hpp"

namespace Engine::Maths
{
    class Matrix4f
    {
    public:
        float _values[16];

        Vector3f MultiplyPoint(Vector3f rhs);
        Vector3f MultiplyDirection(Vector3f rhs);

        void Translate(Vector3f translation);
        void Rotate(Vector3f rotation);
        void Scale(Vector3f scale);

        void Transpose();
        void Invert();

        static Matrix4f identity;
    };
}

