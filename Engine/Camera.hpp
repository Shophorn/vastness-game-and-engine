/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Transform.hpp"
#include "VectorsAndMatrices.hpp"

namespace Engine
{
    class Camera
    {
    public:
        vec3 position;
        float fieldOfView = 45.0f;
        float near = 0.01f;
        float far = 100.0f;
        float aspectRatio;

        mat4 viewMatrix()
        {
            return glm::lookAt(position, vec3(0.0f,0.0f,0.0f), vec3(0.0f,0.0f,1.0f));
        }

        mat4 projectionMatrix ()
        {
            return glm::perspective(fieldOfView, aspectRatio, near, far);
        }
    };
}