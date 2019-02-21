/*
Leo Tamminen
21/11/2018
*/

#include "Engine/Engine.hpp"

int main()
{
#define ENGINE_NEW
#ifdef ENGINE_NEW
    Engine engine;
    engine.initialize("Vastness", 1920, 1080);

    while(engine.isRunning())
    {
        engine.handleEvents();
        engine.update();
        engine.render();
    }

    engine.terminate();
#else
    using namespace Core;
    using namespace Core::Collections;
    using namespace Core::Maths;

    // TO engine ----


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

    // TO engine ----

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
#endif

}