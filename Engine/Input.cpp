/*
LeoTamminen
Created 26/12/2018
*/

#include "Input.hpp"
#include <GLFW/glfw3.h>

using  namespace Core;

GLFWwindow * Input::_window = nullptr;

float Input::horizontal()
{
    bool left = glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS;
    bool right = glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS;

    return
        (left ? -1.0f : 0.0f)
        + (right ? 1.0f : 0.0f);
}

float Input::vertical()
{
    bool down = glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS;
    bool up = glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS;

    return
        (down ? -1.0f : 0.0f)
        + (up ? 1.0f : 0.0f);
}
