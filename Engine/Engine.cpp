/*
Shophorn Games
Leo Tamminen
Created 13/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DEBUG.hpp"
#include "Engine.hpp"
#include "Rendering/RenderManager.hpp"
#include "ECS.hpp"
#include "Input.hpp"

#include "EcsCoreComponents.hpp"
#include "SceneLoader.hpp"

ECS core::ecs;
Input core::input;
RenderManager core::renderManager;

void Engine::handleEvents()
{
    glfwPollEvents();
    _isRunning = !glfwWindowShouldClose(_window);
    core::input.update();
}

void Engine::update()
{
    float deltaTime = 0.01f;
    core::ecs.update(deltaTime);
}

void Engine::render()
{
    core::ecs.onBeforeRender();
    core::renderManager.render();
    glfwSwapBuffers(_window);
}

void Engine::start()
{

    _isRunning = true;
    while (_isRunning)
    {
        handleEvents();
        update();
        render();
    }
}

bool Engine::loadScene(const char * path)
{
   ecsLoader->build(path);

   // make use of this
   return true;
}

void Engine::terminate()
{
    core::renderManager.terminate();
    core::ecs.terminate();
    core::input.terminate();
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
    ecs = &core::ecs;

    initializeCoreComponents(&core::ecs);
    initializeCoreSystems(&core::ecs);

    ecsLoader = std::make_unique<SceneLoader>();
    ecsLoader->registerDeserializers(getCoreDeserializeFunctions());
}
