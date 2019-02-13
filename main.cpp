/*
Leo Tamminen
21/11/2018
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Collections/Array.hpp"
#include "Engine/Entity.hpp"
#include "Engine/Input.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Screen.hpp"
#include "Engine/SceneLoader.hpp"
#include "Engine/SpriteAnimator.hpp"

//#include <stdio.h>
#include <iostream>
#include <string>


#include "Engine/Maths/Maths.hpp"
#include "Engine/Collisions/CollisionManager.hpp"

int main()
{
    using namespace Engine;
    using namespace Engine::Collections;
    using namespace Engine::Maths;

    const char * gamePath = "Game/game.json";

    Screen screen = SceneLoader::LoadContext(gamePath);

    glewExperimental = GL_TRUE;
    glewInit();
    Input::Initialize(screen.window());

    Scene scene = SceneLoader::Load(gamePath);
    scene.camera.aspectRatio = screen.aspectRatio();

    Array<Entity*> & actors = scene.entities;
    Array<Renderer*> & renderers = scene.renderers;


    for (const auto &shader : scene.shaders)
    {
        shader.second.Use();
        Vector3f ambientColor (0.05, 0.08, 0.2);
        glUniform3fv(glGetUniformLocation(shader.second.id, "_Ambient"), 1, (float*)&ambientColor);
    }

    glEnable(GL_DEPTH_TEST);

    // Remember to use glFinish()
    double lastTime = 0.0;
    float deltaTime = 0.0f;
    glfwSwapInterval(1);

    CollisionManager::startUp();

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
        int i = 0;
        for (auto * actor : actors)
        {
            actor->update(deltaTime);
        }

        Array<SpriteAnimator> sprites;
        for (auto sprite : sprites)
        {
            sprite.Update(deltaTime);
        }

        // Render
        for (const auto &shader : scene.shaders)
        {
            shader.second.Use();

            glUniformMatrix4fv(shader.second.viewLocation, 1, false, &scene.camera.viewMatrix()[0][0]);
            glUniformMatrix4fv(shader.second.projectionLocation, 1, false, &scene.camera.projectionMatrix()[0][0]);
            glUniform3fv(shader.second.cameraPosLocation, 1, (float*)&scene.camera.position);
            glUniform3fv(shader.second.lightDirLocation, 1, (float*)&scene.light.direction);
            glUniform3fv(shader.second.lightColorLocation, 1, (float*)&scene.light.color);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < renderers.count(); i++) {
            renderers[i]->Draw();
        }

        glfwSwapBuffers(screen.window());
    }

}