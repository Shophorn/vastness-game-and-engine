/*
LeoTamminen
Created 13/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "DEBUG.hpp"
#include "Engine.hpp"
#include "Rendering/RenderManager.hpp"
#include "ECS/ECS.hpp"
#include "ECS/List.hpp"
#include "Input.hpp"
#include <cmath>

ecs core::ecs;
Input core::input;

void Engine::handleEvents()
{
    glfwPollEvents();
    _isRunning = !glfwWindowShouldClose(_window);
}

void Engine::update()
{
    float deltaTime = 1.0f;
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


struct position
{
    float x, y, z;
};

struct scale
{
    float x, y, z;
};

struct move
{
    float speed;
};


struct movementSystem
{
    using components = mtl::List<position, move>;

    void update(position& pos, move& mv, float deltaTime)
    {
        pos.x += mv.speed;
        cout << pos.x << "\n";
    }
};

struct playerControlTag{};

struct playerControlSystem
{
    using components = mtl::List<move, playerControlTag>;

    void update(move& mv, playerControlTag & tag, float deltaTime)
    {
        mv.speed = core::input.horizontal();
    }
};


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

    using core::ecs;

    // move component registering to system registering, maybe
    ecs.registerComponent<position>();
    ecs.registerComponent<scale>();
    ecs.registerComponent<move>();
    ecs.registerComponent<playerControlTag>();

    ecs.registerSystem<movementSystem>();
    ecs.registerSystem<playerControlSystem>();

    Handle player = ecs.createEntity();
    ecs.addComponent<move>(player);
    ecs.addComponent<position>(player);
    ecs.addComponent<playerControlTag>(player);

    _isRunning = true;
}

