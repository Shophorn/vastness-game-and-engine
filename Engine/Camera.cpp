/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#include <GL/glew.h>
#include "Camera.hpp"

Camera::Camera(
        vector3f _position,
        vector3f _target,
        float _fieldOfView,
        float _nearClippingPlane,
        float _farClippingPlane,
        vector3f _clearColor
){
    position = _position;
    target = _target;
    fieldOfView = _fieldOfView;
    nearClippingPlane = _nearClippingPlane;
    farClippingPlane = _farClippingPlane;

    SetClearColor(_clearColor);
}

void Camera::SetClearColor(vector3f color)
{
    _clearColor = color;
    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0);
}

matrix4f Camera::viewMatrix()
{
    // Look here
    // https://stackoverflow.com/questions/21830340/understanding-glmlookat
    vector3f forward = normalize(position - target);
    vector3f right = cross(vector3f::up, forward);
    vector3f up = cross(forward, right);

    vector3f nPosition = -position;

    matrix4f mat;
    mat[0] = vector4f(right.x, up.x, forward.x, 0);
    mat[1] = vector4f(right.y, up.y, forward.y, 0);
    mat[2] = vector4f(right.z, up.z, forward.z, 0);
    mat[3] = vector4f(dot(right, nPosition), dot (up, nPosition), dot(forward, nPosition), 1);

    return mat;

}

matrix4f Camera::projectionMatrix()
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

    matrix4f mat;
    mat[0] = vector4f(f / aspectRatio, 0, 0, 0);
    mat[1] = vector4f(0, f, 0, 0);
    mat[2] = vector4f(0, 0, m22, -1);
    mat[3] = vector4f(0, 0, m23, 0);

    return mat;

}
