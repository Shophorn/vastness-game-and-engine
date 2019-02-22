/*
LeoTamminen
Created 16/02/2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include "../DEBUG.hpp"
#include "RenderManager.hpp"
#include "RendererSystem.hpp"
#include "../Maths/Maths.hpp"
#include "../TransformComponent.hpp"
#include "../Shader.hpp"
#include "../Mesh.hpp"
#include "../AssetLoader.hpp"
#include "../Camera.hpp"



GLuint testVao;
int testElementCount;
std::unique_ptr<Mesh> testMesh;
matrix4f testView;
matrix4f testProjection;

void RenderManager::initialize()
{
    glClearColor(0.6, 0.8, 1.0, 1.0);
    _shaders.emplace_back(shader::Load("default"));

    Mesh mesh;
    AssetLoader::LoadOBJ("Assets/Cube.obj", &mesh);
    testMesh = std::make_unique<Mesh>(std::move(mesh));
    testMesh->LoadToGL(_shaders[0u].id);
    testVao = testMesh->vao();
    testElementCount = testMesh->elementCount();

    Camera testCamera(vector3f(0, 5, 2), vector3f(0), 45, 0, 100, vector3f(0.6, 0.8, 1.0));
    testCamera.aspectRatio = 1920.0f / 1080.0f;
    testProjection = testCamera.projectionMatrix();
    testView = testCamera.viewMatrix();

    debug << testView << "\n\n"<< testProjection << "\n";
}

void RenderManager::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto & rd : _toRender)
    {
        glUniformMatrix4fv(_shaders[rd.shader].modelLocation, 1, GL_FALSE, &rd.model[0][0]);
        glUniformMatrix4fv(_shaders[rd.shader].modelITLocation, 1, GL_TRUE, &rd.inverse[0][0]);

        glUniformMatrix4fv(_shaders[rd.shader].viewLocation, 1, GL_FALSE, &testView[0][0]);
        glUniformMatrix4fv(_shaders[rd.shader].projectionLocation, 1, GL_FALSE, &testProjection[0][0]);

        glUseProgram(_shaders[rd.shader].id);
        glBindVertexArray(testVao);

        glDrawElements(GL_TRIANGLES, testElementCount, GL_UNSIGNED_INT, nullptr);
    }

    // bind vao
    // bind texture
    // use shader
    // set values

//    cout << "Rendering " << toRenders.size() << " objects : " << glfwGetTime() << "\n";

    _toRender.clear();
    glFinish();
}



void RenderManager::addRenderer(const transform &tr, const renderer &r)
{
    _toRender.emplace_back(renderData {modelMatrix(tr), inverseModelMatrix(tr)});
}

void RenderManager::terminate()
{
    for (const auto & s : _shaders)
        glDeleteShader(s.id);

    _shaders.clear();
}

