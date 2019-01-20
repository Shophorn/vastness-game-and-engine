/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

namespace Engine
{
    using vec3 = glm::vec3;
    using mat4 = glm::mat4;

    namespace Vector3
    {
        extern vec3 down;
        extern vec3 up;
        extern vec3 left;
        extern vec3 right;
        extern vec3 back;
        extern vec3 forward;
    }
}
