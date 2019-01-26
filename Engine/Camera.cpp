/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#include <GL/glew.h>
#include "Camera.hpp"

using namespace Engine;

Camera::Camera(
    vec3 _position,
    vec3 _target,
    float _fieldOfView,
    float _nearClippingPlane,
    float _farClippingPlane,
    vec3 _clearColor
){
    position = _position;
    target = _target;
    fieldOfView = _fieldOfView;
    nearClippingPlane = _nearClippingPlane;
    farClippingPlane = _farClippingPlane;

    SetClearColor(_clearColor);
}

void Camera::SetClearColor(vec3 color)
{
    _clearColor = color;
    glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], 1.0);
}
