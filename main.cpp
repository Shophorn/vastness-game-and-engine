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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
int main()
{
    using namespace Engine;
    using namespace Engine::Collections;
    using namespace Engine::Maths;

    /*
    Matrix4f A {
        Vector4f(1, 3, 5, 0),
        Vector4f(0, 1, 0, 0),
        Vector4f(7, 0, 1, 0),
        Vector4f(0, 0, 0, 1)
    };

    std::cout << A << "\n";
    A.transpose();
    std::cout << A << "\n";

    Matrix4f B {
            Vector4f(2, 0, 0, 0),
            Vector4f(0, 1, 0, 0),
            Vector4f(0, 0, 3, 0),
            Vector4f(0, 0, 0, 1)
    };

    std::cout << A << "\n" << B << "\n" << A * B << "\n";
    Vector3f pos (10.3f, 2.4f, 1.0f);
    Vector3f rot (0);
    Vector3f scale (2.0, 3.0, 1.0);

    Transform tester (pos, rot, scale);
    auto MM = tester.modelMatrixNew();
    auto IM = tester.inverseModelMatrix();

    std::cout << "MM\n" << MM << "\nIM:\n" << IM << "\nmultiplied\n" << MM * IM << "\n";

    IM.transpose();
    glm::mat4 modelITXX = glm::transpose(glm::inverse(tester.modelMatrix()));
    Matrix4f aaa {
            Vector4f(modelITXX[0][0], modelITXX[0][1], modelITXX[0][2], modelITXX[0][3]),
            Vector4f(modelITXX[1][0], modelITXX[1][1], modelITXX[1][2], modelITXX[1][3]),
            Vector4f(modelITXX[2][0], modelITXX[2][1], modelITXX[2][2], modelITXX[2][3]),
            Vector4f(modelITXX[3][0], modelITXX[3][1], modelITXX[3][2], modelITXX[3][3]),
    };

    std::cout << "glm inverse\n" << aaa << "\ncustom\n" << IM << "\n";
*/

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