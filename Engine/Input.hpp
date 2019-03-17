/*
LeoTamminen
Created 26/12/2018
*/

#pragma once

#include "Maths/vector2f.hpp"

class GLFWwindow;

class Input
{
private:
    GLFWwindow * _window = nullptr;

    maths::vector2f _mousePosition;
    maths::vector2f _mouseMovement;

public:
    void initialize(GLFWwindow *window);
    void update();
    void terminate() {}

    float horizontal(int controller);
    float vertical(int controller);

    maths::vector2f mouseMovement(int controller) { return _mouseMovement; }
};

namespace core
{
    extern Input input;
}