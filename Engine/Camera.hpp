/*
LeoTamminen
Created 27/12/2018
*/

#pragma once

#include "Transform.hpp"
#include "Maths/matrix4f.hpp"
namespace Core
{
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

        void SetClearColor(vector3f color);

        Camera () = default;

        Camera(
                vector3f _position,
                vector3f _target,
                float _fieldOfView,
                float _nearClippingPlane,
                float _farClippingPlane,
                vector3f _clearColor
        );


        Maths::matrix4f viewMatrix()
        {
            // Look here
            // https://stackoverflow.com/questions/21830340/understanding-glmlookat
            vector3f forward = normalize(position - target);
            vector3f right = cross(vector3f::up, forward);
            vector3f up = cross(forward, right);

            vector3f nPosition = -position;

            Maths::matrix4f mat;
            mat[0] = Maths::Vector4f(right.x, up.x, forward.x, 0);
            mat[1] = Maths::Vector4f(right.y, up.y, forward.y, 0);
            mat[2] = Maths::Vector4f(right.z, up.z, forward.z, 0);
            mat[3] = Maths::Vector4f(dot(right, nPosition), dot (up, nPosition), dot(forward, nPosition), 1);

            return mat;

        }

        bool printed = false;
        Maths::matrix4f projectionMatrix()
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

            Maths::matrix4f mat;
            mat[0] = Maths::Vector4f(f / aspectRatio, 0, 0, 0);
            mat[1] = Maths::Vector4f(0, f, 0, 0);
            mat[2] = Maths::Vector4f(0, 0, m22, -1);
            mat[3] = Maths::Vector4f(0, 0, m23, 0);

            return mat;

        }
    };
}