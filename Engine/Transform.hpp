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
        vec3 position = vec3(0.0f, 0.0f, 0.0f);
        vec3 rotation = vec3(0.0f, 0.0f, 0.0f);

        // Initialize to zero position and rotation
        Transform() : position(vec3(0,0,0)), rotation(vec3(0,0,0)){}
        Transform(vec3 pos, vec3 rot) : position(pos), rotation(rot) {}
        Transform(const Transform &other) = default;

        mat4 model()
        {
            mat4 m = mat4(1.0f);
            m = glm::translate(m, position);

            m = glm::rotate(m, glm::radians(rotation.z), Vector3::up);
            m = glm::rotate(m, glm::radians(rotation.y), Vector3::forward);
            m = glm::rotate(m, glm::radians(rotation.x), Vector3::right);

            return m;
        }

    };

}


