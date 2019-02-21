/*
LeoTamminen
Created 26/12/2018
*/

#pragma once

class GLFWwindow;

class Input
{
private:
    GLFWwindow *_window = nullptr;

public:
    void initialize(GLFWwindow *window){ _window = window; }

    float horizontal();
    float vertical();
};

namespace core
{
    extern Input input;
}