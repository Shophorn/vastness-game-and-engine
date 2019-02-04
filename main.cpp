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


#include "Engine/Maths/Vector3f.hpp"
int main()
{
    using namespace Engine;
    using namespace Engine::Collections;
    using namespace Engine::Maths;



    Vector3f pos (10.3, 2.4, 1.0);
    Vector3f rot (0);
    Vector3f scale (1);

    Transform tester (pos, rot, scale);
    auto MM = tester.modelMatrixNew();
    auto IM = tester.inverseModelMatrix();

    std::cout << "position\n" << Matrix4f::translate(pos) << "\n";

    std::cout << "MM\n" << MM << "\nIM:\n" << IM << "\nmultiplied\n" << MM * IM << "\n";


    const char * gamePath = "Game/game.json";

    Screen screen = SceneLoader::LoadContext(gamePath);

    glewExperimental = GL_TRUE;
    glewInit();
    Input::Initialize(screen.window());


    Scene scene = SceneLoader::Load(gamePath);
    scene.camera.aspectRatio = screen.aspectRatio();

    Array<Entity*> & actors = scene.actors;
    Array<Renderer*> & renderers = scene.renderers;


    for (const auto &shader : scene.shaders)
    {
        shader.second.Use();

        glUniformMatrix4fv(shader.second.viewLocation, 1, false, &scene.camera.viewMatrix()[0][0]);
        glUniformMatrix4fv(shader.second.projectionLocation, 1, false, &scene.camera.projectionMatrix()[0][0]);
        glUniform3fv(shader.second.cameraPosLocation, 1, (float*)&scene.camera.position);
        glUniform3fv(shader.second.lightDirLocation, 1, (float*)&scene.light.direction);
        glUniform3fv(shader.second.lightColorLocation, 1, (float*)&scene.light.color);
    }

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
        int i = 0;
        for (auto * actor : actors)
        {
            actor->Update(deltaTime);
        }

        Array<SpriteAnimator> sprites;
        for (auto sprite : sprites)
        {
            sprite.Update(deltaTime);
        }

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < renderers.count(); i++) {
            renderers[i]->Draw();
        }
        glfwSwapBuffers(screen.window());
    }
}