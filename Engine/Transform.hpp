/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include "Maths/Maths.hpp"

namespace Core
{
    class Transform
    {
    public:
        maths::vector3f position;
        maths::vector3f rotation;
        maths::vector3f scale;

        // Initialize to zero position and rotation
        Transform() : position(vector3f(0)), rotation(vector3f(0)), scale(vector3f(1)){}

        Transform(const vector3f & _position, const vector3f & _rotation, const vector3f & _scale) :
            position(maths::vector3f(_position.x, _position.y, _position.z)),
            rotation(maths::vector3f(_rotation.x, _rotation.y, _rotation.z)),
            scale(maths::vector3f(_scale.x, _scale.y, _scale.z))
            {}

        Transform(const Transform &other) = default;

        maths::matrix4f modelMatrixNew() const;
        maths::matrix4f inverseModelMatrix() const;
    };

}


