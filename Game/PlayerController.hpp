/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#pragma once

#include "../Engine/Entity.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Transform.hpp"
#include "../Engine/SpriteAnimator.hpp"

using namespace Engine;

namespace Game
{
    class PlayerController : public Entity
    {
    public:
        Transform * transform = nullptr;
        SpriteAnimator * animator = nullptr;
        Renderer * renderer = nullptr;

        float moveSpeed = 0;

        PlayerController(Transform * transform, float moveSpeed)
            : transform(transform), moveSpeed(moveSpeed) {}

        void Update(float deltaTime) final;
    };
}

