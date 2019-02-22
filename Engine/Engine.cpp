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
#include <cmath>
#include "Rendering/RenderSystem.hpp"

ecs core::ecs;
Input core::input;

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
    using components = mtl::List<position, move, scale>;

    void update(position& pos, move& mv, float deltaTime)
    {
        pos.x += mv.speed;
//        cout << pos.x << "\n";
    }
};

struct playerControl
{
    float speed = 1.0f;
};

struct playerControlSystem
{
    using components = mtl::List<transform, playerControl>;

    void update(transform & tr, playerControl & pl, float deltaTime)
    {
         tr.position.x += core::input.horizontal() * deltaTime * pl.speed;
         tr.position.y += core::input.vertical() * deltaTime * pl.speed;
    }
};

struct followEntity
{
    Handle handle;
    float speed{};
};

struct followEntitySystem
{
    using components = mtl::List<followEntity, transform>;

    void update(const followEntity & fe, transform & tr, float dt)
    {
        vector3f target = core::ecs.getComponent<transform>(fe.handle).position;
        vector3f movement = target - tr.position;
        float m = magnitude(movement);
        if (m > 1.0)
            movement /= m;
        tr.position += fe.speed * dt * movement;
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
    ecs.registerComponent<playerControl>();
    ecs.registerComponent<renderer>();
    ecs.registerComponent<transform>();
    ecs.registerComponent<followEntity>();

    ecs.registerSystem<movementSystem>();
    ecs.registerSystem<playerControlSystem>();
    ecs.registerSystem<rendererSystem>();
    ecs.registerSystem<followEntitySystem>();

//#define TEST
#if defined TEST
    int testCount = 1000;

    std::vector<Handle> handles;
    handles.reserve(testCount);

    for (int i = 0; i < testCount; i++)
    {
        handles[i] = ecs.createEntity();
        ecs.addComponent<transform>(handles[i]);
        ecs.addComponent<renderer>(handles[i]);
    }
#endif
    Handle player = ecs.createEntity();
    ecs.addComponent<playerControl>(player);
    ecs.addComponent<transform>(player);
    ecs.addComponent<renderer>(player);

    Handle e1 = ecs.createEntity();
    ecs.addComponent<transform>(e1, vector3f(0), vector3f(1), vector3f(0.5));
    ecs.addComponent<renderer>(e1);
    ecs.addComponent<followEntity>(e1, player, 0.1f);

    Handle e2 = ecs.createEntity();
    ecs.addComponent<transform>(e2, vector3f(2, 0 ,0), vector3f(1), vector3f(0.5));
    ecs.addComponent<renderer>(e2);
    ecs.addComponent<followEntity>(e2, e1, 0.1f);

    _isRunning = true;
}

