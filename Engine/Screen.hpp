/*
Leo Tamminen
Created 22/11/2018
*/

#pragma once
#include <GLFW/glfw3.h>

namespace  Core
{
    class Screen
    {
    private:
        int _width;
        int _height;

        GLFWwindow * _window;

        Screen(int width, int height) : _width(width), _height(height) {}

    public:

        ~Screen() { glfwTerminate(); }

        int width() { return _width; }
        int height() { return _height; }
        float aspectRatio() { return (float) _width / (float) _height; }

        GLFWwindow * window(){ return _window; }

        static Screen Create(const char *title, int width, int height)
        {
            Screen window(width, height);

            // Create context
            glfwInit();

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

            glfwWindowHint(GLFW_RESIZABLE, true);
            window._window = glfwCreateWindow(width, height, title, nullptr, nullptr);
            glfwMakeContextCurrent(window._window);

            return window;
        }
    };
}