/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "VectorsAndMatrices.hpp"

namespace Engine
{
    struct Light
    {
        vec3 direction;
        vec3 color;
        float intensity;

        Light(){}

        Light(vec3 direction, vec3 color, float intensity)
            : direction(direction), color(color), intensity(intensity) {}

    };
}