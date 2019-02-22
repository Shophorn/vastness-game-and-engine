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
        Maths::vector3f position;
        Maths::vector3f rotation;
        Maths::vector3f scale;

        // Initialize to zero position and rotation
        Transform() : position(vector3f(0)), rotation(vector3f(0)), scale(vector3f(1)){}

        Transform(const vector3f & _position, const vector3f & _rotation, const vector3f & _scale) :
            position(Maths::vector3f(_position.x, _position.y, _position.z)),
            rotation(Maths::vector3f(_rotation.x, _rotation.y, _rotation.z)),
            scale(Maths::vector3f(_scale.x, _scale.y, _scale.z))
            {}

        Transform(const Transform &other) = default;

        Maths::matrix4f modelMatrixNew() const;
        Maths::matrix4f inverseModelMatrix() const;
    };

}


