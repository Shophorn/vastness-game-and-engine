/*
Shophorn
Leo Tamminen
Created 27/12/2018
*/

#include <GL/glew.h>
#include "Camera.hpp"

using namespace Engine;

Camera::Camera(
        Vector3f _position,
        Vector3f _target,
        float _fieldOfView,
        float _nearClippingPlane,
        float _farClippingPlane,
        Vector3f _clearColor
){
    position = _position;
    target = _target;
    fieldOfView = _fieldOfView;
    nearClippingPlane = _nearClippingPlane;
    farClippingPlane = _farClippingPlane;

    SetClearColor(_clearColor);
}

void Camera::SetClearColor(Vector3f color)
{
    _clearColor = color;
    glClearColor(_clearColor.x, _clearColor.y, _clearColor.z, 1.0);
}
