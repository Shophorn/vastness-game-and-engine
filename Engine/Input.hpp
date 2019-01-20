/*
LeoTamminen
Created 26/12/2018
*/

#pragma once

#include <GLFW/glfw3.h>

namespace Engine
{
    class Input
    {
    private:
        static GLFWwindow *_window;

    public:
        static void Initialize(GLFWwindow * window) { _window = window; }

        static float horizontal();

        static float vertical();
    };
}

