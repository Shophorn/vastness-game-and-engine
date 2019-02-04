/*
LeoTamminen
Created 16/12/2018
*/

#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

namespace Engine
{
    using vec3 = glm::vec3;
    using mat4 = glm::mat4;
}
std::ostream & operator << (std::ostream & os, const glm::vec3 & v);
