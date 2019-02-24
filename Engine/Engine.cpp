/*
LeoTamminen
Created 13/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DEBUG.hpp"
#include "Engine.hpp"
#include "Rendering/RenderManager.hpp"
#include "ECS.hpp"
#include "Input.hpp"

#include "ECSTest.hpp"

ecs core::ecs;
Input core::input;
RenderManager core::renderManager;

void Engine::handleEvents()
{
    glfwPollEvents();
    _isRunning = !glfwWindowShouldClose(_window);
}

void Engine::update()
{
    float deltaTime = 0.01f;
    core::ecs.update(deltaTime);
}

void Engine::render()
{
    core::renderManager.render();
    glfwSwapBuffers(_window);
}

void Engine::terminate()
{
    glfwTerminate();
}

void Engine::initialize(const char *title, int width, int height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    glewInit();

    core::renderManager.initialize();
    core::input.initialize(_window);
    core::ecs.initialize();

    test::testECS();

    _isRunning = true;
}

