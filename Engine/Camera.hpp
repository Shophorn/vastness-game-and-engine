/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Maths/Maths.hpp"

class Camera
{
    private:
        vector3f _clearColor;

    public:
        vector3f position;
        vector3f target;
        float fieldOfView;
        float nearClippingPlane;
        float farClippingPlane;
        float aspectRatio;

        Camera () = default;

        Camera(
            vector3f _position,
            vector3f _target,
            float _fieldOfView,
            float _nearClippingPlane,
            float _farClippingPlane,
            vector3f _clearColor
        );

        matrix4f viewMatrix();
        matrix4f projectionMatrix();
        void SetClearColor(vector3f color);
};
