/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#pragma once

#include "../Engine/Renderer.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/Transform.hpp"
#include "../Engine/SpriteAnimator.hpp"
#include "../Engine/Camera.hpp"

using namespace Core;

namespace Game
{
    class PlayerController// : public Entity
    {
    public:
        Camera *camera = nullptr;
        Transform *transform = nullptr;
        SpriteAnimator *animator = nullptr;
        Renderer *renderer = nullptr;

        float moveSpeed = 0;
        vector3f cameraOffset;

        PlayerController() = default;

        PlayerController(Transform *transform, float moveSpeed)
                : transform(transform), moveSpeed(moveSpeed) {}

        void start();
        void update(float deltaTime);
    };
}
