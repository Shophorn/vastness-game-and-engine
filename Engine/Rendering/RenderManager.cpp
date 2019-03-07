/*
LeoTamminen
Created 16/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

#include "../Camera.hpp"
#include "RenderManager.hpp"
#include "RendererSystem.hpp"
#include "../Maths/Maths.hpp"
#include "../TransformComponent.hpp"
#include "../Shader.hpp"
#include "../Mesh.hpp"
#include "../Loader.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"

matrix4f testView;
matrix4f testProjection;

void RenderManager::initialize()
{
    glClearColor(0.6, 0.8, 1.0, 1.0);

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

    for (const auto & rd : _toRender)
    {
        // todo sort : shader -> mesh -> entity
        auto shader = resources::shaders.get(rd.handle.shader);
        auto mesh = resources::meshes.get(rd.handle.mesh);

        // per frame
        glUseProgram(shader.id);
        glUniformMatrix4fv(shader.viewLocation, 1, GL_FALSE, &testView[0][0]);
        glUniformMatrix4fv(shader.projectionLocation, 1, GL_FALSE, &testProjection[0][0]);

        // per entity = renderdata
        glUniformMatrix4fv(shader.modelLocation, 1, GL_FALSE, &rd.model[0][0]);
        glUniformMatrix4fv(shader.modelITLocation, 1, GL_TRUE, &rd.inverse[0][0]);
        glBindVertexArray(mesh.vao);
        glBindTexture(GL_TEXTURE_2D, rd.texture);

        glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, nullptr);
    }

    _toRender.clear();
    glFinish();
}

void RenderManager::addDrawCall(const transform &tr, const renderer &r)
{
    _toRender.emplace_back(
        renderData {
            modelMatrix(tr),
            inverseModelMatrix(tr),
            r.texture,
            r.handle
    });
}

void RenderManager::terminate() {}

RenderManager::renderHandle RenderManager::bindRenderInfo(int shader, meshHandle mesh)
{
//    for (const auto & h : _renderHandles){
//        if (h.shader == shader && h.mesh == mesh){
//            return h;
//        }
//    }

    // bind together and save
//    mesh = resources::meshes.instantiate(mesh);
    setVertexAttributes(resources::meshes.get(mesh), resources::shaders.get(shader));
    return _renderHandles.emplace_back( renderHandle{ shader, mesh} );
}
