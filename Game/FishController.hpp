/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "../Engine/Actor.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Transform.hpp"

using namespace Engine;

namespace Game
{
    class FishController : public Actor
    {
    public:
        Transform * transform;
        vec3 rotation;

        FishController(Transform * transform, vec3 rotation)
            : transform(transform), rotation(rotation) {}

        void Update(float deltaTime) final;
    };
}


