/*
Leo Tamminen
21/11/2018
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Collections/Array.hpp"
#include "Engine/Actor.hpp"
#include "Engine/Input.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Screen.hpp"
#include "Engine/SceneLoader.hpp"

//#include <stdio.h>
#include <iostream>
#include <string>

#include "Engine/Collections/Dictionary.hpp"
#include "Engine/StringOperations.hpp"

int main()
{
    using namespace Engine;
    using namespace Engine::Collections;

    Screen screen = Screen::Create("Fishness", 1920, 1080);
    glewExperimental = GL_TRUE;
    glewInit();
    Input::Initialize(screen.window());


    Scene scene = SceneLoader::Load("Game/game.json");
    scene.camera.aspectRatio = screen.aspectRatio();

    std::cout << "Hello\n";

    Array<Actor*> & actors = scene.actors;
    Array<Renderer*> & renderers = scene.renderers;

    for (const auto &shader : scene.shaders)
    {
        shader.second.Use();

        glUniformMatrix4fv(shader.second.viewLocation, 1, false, glm::value_ptr(scene.camera.viewMatrix()));
        glUniformMatrix4fv(shader.second.projectionLocation, 1, false, glm::value_ptr(scene.camera.projectionMatrix()));
        glUniform3fv(shader.second.cameraPosLocation, 1, glm::value_ptr(scene.camera.position));
        glUniform3fv(shader.second.lightDirLocation, 1, glm::value_ptr(scene.light.direction));
    }

    glClearColor(0.046f, 0.102f, 0.24f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Remember to use glFinish()
    double lastTime = 0.0;
    float deltaTime = 0.0f;
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(screen.window()))
    {
        // Time things, need to sync threads with glFinish, may be a laptop issue
        glFinish();
        double time = glfwGetTime();
        deltaTime = (float)(time - lastTime);
        lastTime = time;

        // Input
        glfwPollEvents();
        // Update input??

        // Simulate
        for (auto * actor : actors)
//        for (int i = 0; i <actors.count(); i++)
        {
            actor->Update(deltaTime);
//            actors[i]->Update(deltaTime);
        }

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < renderers.count(); i++) {
            renderers[i]->Draw();
        }
        glfwSwapBuffers(screen.window());
    }
}