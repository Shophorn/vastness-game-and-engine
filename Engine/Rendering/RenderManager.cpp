/*
LeoTamminen
Created 16/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

#include "../DEBUG.hpp"
#include "RenderManager.hpp"
#include "RendererSystem.hpp"
#include "../Maths/Maths.hpp"
#include "../TransformComponent.hpp"
#include "../Shader.hpp"
#include "../Mesh.hpp"
#include "../Loader.hpp"
#include "../Camera.hpp"
#include "../Stopwatch.hpp"



GLuint testVao;
int testElementCount;
matrix4f testView;
matrix4f testProjection;

void RenderManager::initialize()
{
    glClearColor(0.6, 0.8, 1.0, 1.0);

    Camera testCamera(vector3f(0, 5, 2), vector3f(0), 45, 0, 100, vector3f(0.6, 0.8, 1.0));
    testCamera.aspectRatio = 1920.0f / 1080.0f;
    testProjection = testCamera.projectionMatrix();
    testView = testCamera.viewMatrix();
}

void RenderManager::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto sw = Stopwatch::startNew();

    for (const auto & rd : _toRender)
    {
        // todo: sort
        auto _shader = getShader(rd.shaderHandle);
        auto mesh = core::meshes.get(rd.meshHandle);

        glUseProgram(_shader.id);

        glUniformMatrix4fv(_shader.modelLocation, 1, GL_FALSE, &rd.model[0][0]);
        glUniformMatrix4fv(_shader.modelITLocation, 1, GL_TRUE, &rd.inverse[0][0]);

        glUniformMatrix4fv(_shader.viewLocation, 1, GL_FALSE, &testView[0][0]);
        glUniformMatrix4fv(_shader.projectionLocation, 1, GL_FALSE, &testProjection[0][0]);

        glBindVertexArray(mesh.vao);
        glBindTexture(GL_TEXTURE_2D, rd.texture);
        glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, nullptr);
    }

    debug << "rendering took " << sw.seconds() * 1000 << " ms\n";

    _toRender.clear();
    glFinish();
}

void RenderManager::addRenderer(const transform &tr,  const renderer & r)
{
    _toRender.emplace_back(
        renderData {
            modelMatrix(tr),
            inverseModelMatrix(tr),
            r.texture,
            r.shaderHandle,
            r.meshHandle
    });
}

void RenderManager::terminate()
{
    for (const auto & s : _shaders)
        glDeleteShader(s.id);

    _shaders.clear();
}

int RenderManager::getShaderHandle(const std::string & name)
{
    if (_shaderMap.find(name) == _shaderMap.end())
    {
        _shaders.emplace_back(Shader::Load(name));
        _shaderMap.emplace(name, _shaders.size() -1);
    }

    return _shaderMap[name];
}
