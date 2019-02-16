/*
LeoTamminen
Created 13/02/2019
*/

#include <GL/glew.h>

#include "Engine.hpp"
#include "Screen.hpp"
#include "Maths/Maths.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "Screen.hpp"
#include "SceneLoader.hpp"
#include "Scene.hpp"
#include "SpriteAnimator.hpp"

void Engine::handleEvents()
{
    glfwPollEvents();
    _isRunning = !glfwWindowShouldClose(_window);
}

void Engine::update() {}
void Engine::render()
{
//    core::renderManager.render();
    glfwSwapBuffers(_window);
}

void Engine::clean()
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
    using namespace Core;
    const char * gamePath = "Game/game.json";


    _isRunning = true;
}
