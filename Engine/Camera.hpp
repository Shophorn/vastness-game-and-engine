/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Transform.hpp"
#include "VectorsAndMatrices.hpp"

namespace Engine
{
    class Camera
    {
    private:
        vec3 _clearColor;

    public:
        vec3 position;
        vec3 target;
        float fieldOfView;
        float nearClippingPlane;
        float farClippingPlane;
        float aspectRatio;

        void SetClearColor(vec3 color);

        Camera () = default;

        Camera(
            vec3 _position,
            vec3 _target,
            float _fieldOfView,
            float _nearClippingPlane,
            float _farClippingPlane,
            vec3 _clearColor
        );

        mat4 viewMatrix()
        {
            return glm::lookAt(position, target, vec3(0.0f,0.0f,1.0f));
        }

        mat4 projectionMatrix ()
        {
            return glm::perspective(fieldOfView, aspectRatio, nearClippingPlane, farClippingPlane);
        }
    };
}