/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include <iomanip>
#include <cmath>

#include "Transform.hpp"
#include "Maths/Matrix4f.hpp"
namespace Engine
{
    class Camera
    {
    private:
        Vector3f _clearColor;

    public:
        Vector3f position;
        Vector3f target;
        float fieldOfView;
        float nearClippingPlane;
        float farClippingPlane;
        float aspectRatio;

        void SetClearColor(Vector3f color);

        Camera () = default;

        Camera(
                Vector3f _position,
                Vector3f _target,
                float _fieldOfView,
                float _nearClippingPlane,
                float _farClippingPlane,
                Vector3f _clearColor
        );


        Maths::Matrix4f viewMatrix()
        {
            // Look here
            // https://stackoverflow.com/questions/21830340/understanding-glmlookat
            Vector3f forward = normalize(position - target);
            Vector3f right = cross(Vector3f::up, forward);
            Vector3f up = cross(forward, right);

            Vector3f nPosition = -position;

            Maths::Matrix4f mat;
            mat[0] = Maths::Vector4f(right.x, up.x, forward.x, 0);
            mat[1] = Maths::Vector4f(right.y, up.y, forward.y, 0);
            mat[2] = Maths::Vector4f(right.z, up.z, forward.z, 0);
            mat[3] = Maths::Vector4f(dot(right, nPosition), dot (up, nPosition), dot(forward, nPosition), 1);

            return mat;

        }

        bool printed = false;
        Maths::Matrix4f projectionMatrix()
        {
            // Orthographic
            //https://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
//            float matGG [4][4] = {
//                {1 / 5.0f , 0, 0, 0},
//                {0, 1 / 5.0f * aspectRatio, 0, 0},
//                {0, 0, -2 / farClippingPlane - nearClippingPlane, 0},
//                {0, 0, 0, 1}
//            };
            // Perspective, same source
            float f = 1.0f / tanf(fieldOfView / 2.0f);
            float m22 = (farClippingPlane + nearClippingPlane) / (nearClippingPlane - farClippingPlane);
            float m23 = (2 * farClippingPlane * nearClippingPlane) / (nearClippingPlane - farClippingPlane);
            float matGG [4][4] = {
                {f / aspectRatio, 0, 0, 0},
                {0, f, 0, 0},
                {0, 0, m22, -1},
                {0, 0, m23, 0}
            };

            Maths::Matrix4f mat;
            mat[0] = Maths::Vector4f(f / aspectRatio, 0, 0, 0);
            mat[1] = Maths::Vector4f(0, f, 0, 0);
            mat[2] = Maths::Vector4f(0, 0, m22, -1);
            mat[3] = Maths::Vector4f(0, 0, m23, 0);

            return mat;

        }
    };
}