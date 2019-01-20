/*
Leo Tamminen
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
    class PlayerController : public Actor
    {
    public:
        Transform * transform = nullptr;
        float moveSpeed = 0;

        PlayerController(Transform * transform, float moveSpeed)
            : transform(transform), moveSpeed(moveSpeed) {}

        void Update(float deltaTime) final;
    };
}

