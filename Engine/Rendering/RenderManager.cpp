/*
Shophorn GAMES
LeoTamminen
Created 16/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

#include "RenderManager.hpp"
#include "RendererSystem.hpp"
#include "../Camera.hpp"
#include "../Maths/Maths.hpp"
#include "../TransformComponent.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"

#include "../DEBUG.hpp"

matrix4f testView;
matrix4f testProjection;

void RenderManager::initialize()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Take care not to set camera near clipping plane to zero, that hyucks up projection and depth test
    Camera testCamera(vector3f(0, 5, 2), vector3f(0), 45, 0.01, 100, vector3f(0.6, 0.8, 1.0));
    testCamera.aspectRatio = 1920.0f / 1080.0f;
    testProjection = testCamera.projectionMatrix();
    testView = testCamera.viewMatrix();

}

void RenderManager::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // todo: sort by shader, and use this nested loop
    for (const auto & shader : resources::shaders)
    {
        // per frame
        glUseProgram(shader.id);
        glUniformMatrix4fv(shader.viewLocation, 1, GL_FALSE, &testView[0][0]);
        glUniformMatrix4fv(shader.projectionLocation, 1, GL_FALSE, &testProjection[0][0]);

        if (lighting.count() > 0)
        {
            glUniform3fv(shader.lightDirLocation, 1, &lighting.begin()->transform.x);
            glUniform3fv(shader.lightColorLocation, 1, &lighting.begin() ->color.r);
        }

        // for renderer etc...
    }

    for (const auto & rd : _drawCalls)
    {
        // todo sort : shader -> mesh -> entity
        auto shader = resources::shaders.get(rd.shader);
        auto mesh = resources::meshes.get(rd.mesh);

        glUseProgram(shader.id);

        // per entity = drawCall
        glUniformMatrix4fv(shader.modelLocation, 1, GL_FALSE, &rd.model[0][0]);
        glUniformMatrix4fv(shader.modelITLocation, 1, GL_TRUE, &rd.inverse[0][0]);

        glBindVertexArray(mesh.vao);
        glBindTexture(GL_TEXTURE_2D, rd.texture);

        glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, nullptr);
    }

    _drawCalls.clear();
    glFinish();
}

void RenderManager::addDrawCall(const transform &tr, const renderer &r)
{
    _drawCalls.emplace_back(
        drawCall {
            modelMatrix(tr),
            inverseModelMatrix(tr),
            r.texture,
            r.shader,
            r.mesh
    });
}

void RenderManager::terminate() {}
