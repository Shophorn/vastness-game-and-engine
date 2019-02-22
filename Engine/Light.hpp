/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Maths/vector3f.hpp"

namespace Core
{
    struct Light
    {
        vector3f direction;
        vector3f color;
        float intensity;

        Light(){}

        Light(vector3f direction, vector3f color, float intensity)
            : direction(direction), color(color), intensity(intensity) {}

    };
}