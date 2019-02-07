/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include "VectorsAndMatrices.hpp"
#include "Maths/Maths.hpp"

namespace Engine
{
    class Transform
    {
    public:
        Maths::Vector3f position;
        Maths::Vector3f rotation;
        Maths::Vector3f scale;

        // Initialize to zero position and rotation
        Transform() : position(Vector3f(0)), rotation(Vector3f(0)), scale(Vector3f(1)){}

        Transform(const Vector3f & _position, const Vector3f & _rotation, const Vector3f & _scale) :
            position(Maths::Vector3f(_position.x, _position.y, _position.z)),
            rotation(Maths::Vector3f(_rotation.x, _rotation.y, _rotation.z)),
            scale(Maths::Vector3f(_scale.x, _scale.y, _scale.z))
            {}

        Transform(const Transform &other) = default;

        Maths::Matrix4f modelMatrixNew() const;
        Maths::Matrix4f inverseModelMatrix() const;
    };

}


