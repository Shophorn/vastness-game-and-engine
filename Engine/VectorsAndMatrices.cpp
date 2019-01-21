/*
Shophorn
Leo Tamminen
Created 16/12/2018
*/

#include "VectorsAndMatrices.hpp"

#include <sstream>

using namespace Engine;

vec3 Vector3::down = vec3(0.0f, 0.0f, -1.0f);
vec3 Vector3::up = vec3(0.0f, 0.0f, 1.0f);
vec3 Vector3::left = vec3(-1.0f, 0.0f, 0.0f);
vec3 Vector3::right = vec3(1.0f, 0.0f, 0.0f);
vec3 Vector3::back = vec3(0.0f, -1.0f, 0.0f);
vec3 Vector3::forward = vec3(0.0f, 1.0f, 0.0f);

std::ostream & operator << (std::ostream & os, const vec3 & v)
{
    std::stringstream ss;
    ss << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
    os << ss.str();
    return os;
}