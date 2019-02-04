/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include "VectorsAndMatrices.hpp"
#include "Maths/Vector3f.hpp"

namespace Engine
{
    class Transform
    {
    public:
        Maths::Vector3f position;
        Maths::Vector3f rotation;
        Maths::Vector3f scale;

        // Initialize to zero position and rotation
        Transform() : position(Maths::Vector3f(0)), rotation(Maths::Vector3f(0)), scale(Maths::Vector3f(1)){}

        Transform(vec3 _position, vec3 _rotation, vec3 _scale) :
            position(Maths::Vector3f(_position.x, _position.y, _position.z)),
            rotation(Maths::Vector3f(_rotation.x, _rotation.y, _rotation.z)),
            scale(Maths::Vector3f(_scale.x, _scale.y, _scale.z))
            {}

        Transform(const Transform &other) = default;

        mat4 modelMatrix()
        {
            mat4 m = mat4(1.0f);
            m = glm::translate(m, vec3(position.x, position.y, position.z));

            m = glm::rotate(m, glm::radians(rotation.z), vec3(0,0,1));
            m = glm::rotate(m, glm::radians(rotation.y), vec3(0,1,0));
            m = glm::rotate(m, glm::radians(rotation.x), vec3(1,0,0));

            m = glm::scale(m, vec3(scale.x, scale.y, scale.z));

            return m;
        }

    };

}


