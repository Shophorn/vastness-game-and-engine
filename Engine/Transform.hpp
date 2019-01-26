/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include "VectorsAndMatrices.hpp"
namespace Engine
{
    class Transform
    {
    public:
        vec3 position;
        vec3 rotation;
        vec3 scale;

        // Initialize to zero position and rotation
        Transform() : position(vec3(0)), rotation(vec3(0)), scale(vec3(1)){}

        Transform(vec3 _position, vec3 _rotation, vec3 _scale) :
            position(_position), rotation(_rotation), scale(_scale) {}

        Transform(const Transform &other) = default;

        mat4 modelMatrix()
        {
            mat4 m = mat4(1.0f);
            m = glm::translate(m, position);

            m = glm::rotate(m, glm::radians(rotation.z), Vector3::up);
            m = glm::rotate(m, glm::radians(rotation.y), Vector3::forward);
            m = glm::rotate(m, glm::radians(rotation.x), Vector3::right);

            m = glm::scale(m, scale);

            return m;
        }

    };

}


