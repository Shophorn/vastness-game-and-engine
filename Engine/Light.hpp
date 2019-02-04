/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Maths/Vector3f.hpp"

namespace Engine
{
    struct Light
    {
        Vector3f direction;
        Vector3f color;
        float intensity;

        Light(){}

        Light(Vector3f direction, Vector3f color, float intensity)
            : direction(direction), color(color), intensity(intensity) {}

    };
}