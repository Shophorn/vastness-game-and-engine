/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

namespace maths
{
    struct matrix4f;
}

#include "Maths/vector3f.hpp"

class Camera
{
    public:
        maths::vector3f _clearColor;
        maths::vector3f position;
        maths::vector3f target;
        float fieldOfView{};
        float nearClippingPlane{};
        float farClippingPlane{};
        float aspectRatio{};

        Camera () = default;

        Camera(
            maths::vector3f _position,
            maths::vector3f _target,
            float _fieldOfView,
            float _nearClippingPlane,
            float _farClippingPlane,
            maths::vector3f _clearColor
        );

        maths::matrix4f viewMatrix();
        maths::matrix4f projectionMatrix();
        void SetClearColor(maths::vector3f color);
};
