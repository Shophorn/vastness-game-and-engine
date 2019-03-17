/*
LeoTamminen
Created 26/12/2018
*/

#include <GLFW/glfw3.h>

#include "Input.hpp"
#include "Maths/Maths.hpp"

#include "DEBUG.hpp"

namespace detail
{
    vector2f getMouseInput(GLFWwindow * window)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return vector2f{static_cast<float>(x), static_cast<float>(y)};
    }
}

void Input::initialize(GLFWwindow * window)
{
    _window = window;
    _mousePosition = detail::getMouseInput(_window);
}

void Input::update()
{
    // for each controller, once they are implemented
    vector2f currentMousePosition = detail::getMouseInput(_window);
    _mouseMovement = currentMousePosition - _mousePosition;
    _mousePosition = currentMousePosition;

    // DEBUG << _mouseMovement << "/" << _mousePosition << "\n";
}

float Input::horizontal(int controller)
{
    bool left = glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS;
    bool right = glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS;

    return
            (left ? -1.0f : 0.0f)
            + (right ? 1.0f : 0.0f);
}

float Input::vertical(int controller)
{
    bool down = glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS;
    bool up = glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS;

    return
            (down ? -1.0f : 0.0f)
            + (up ? 1.0f : 0.0f);
}
