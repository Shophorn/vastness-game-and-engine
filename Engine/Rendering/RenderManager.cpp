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
#include "../CameraComponent.hpp"
#include "../Maths/Maths.hpp"
#include "../TransformComponent.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"

#include "../DEBUG.hpp"

matrix4f testView;
matrix4f testProjection;

namespace
{
    maths::matrix4f viewMatrix(const transform & tr)
    {
        // Look here
        // https://stackoverflow.com/questions/21830340/understanding-glmlookat
        vector3f forward = normalize(tr.position);
        forward = normalize(forward);
        vector3f right = cross(vector3f::up, forward);
        vector3f up = cross(forward, right);

        vector3f nPosition = -tr.position;

        matrix4f mat;
        mat[0] = vector4f(right.x, up.x, forward.x, 0);
        mat[1] = vector4f(right.y, up.y, forward.y, 0);
        mat[2] = vector4f(right.z, up.z, forward.z, 0);
        mat[3] = vector4f(dot(right, nPosition), dot (up, nPosition), dot(forward, nPosition), 1);

        return mat;
    }

    maths::matrix4f projectionMatrix(CameraComponent cam)
    {
            // Orthographic
    //https://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
//            float matGG [4][4] = {
//                {1 / 5.0f , 0, 0, 0},
//                {0, 1 / 5.0f * aspectRatio, 0, 0},
//                {0, 0, -2 / farClippingPlane - nearClippingPlane, 0},
//                {0, 0, 0, 1}
//            };
    // Perspective, same source
    float f = 1.0f / tanf(cam.fieldOfView / 2.0f);
    float m22 = (cam.farClippingPlane + cam.nearClippingPlane) / (cam.nearClippingPlane - cam.farClippingPlane);
    float m23 = (2 * cam.farClippingPlane * cam.nearClippingPlane) / (cam.nearClippingPlane - cam.farClippingPlane);

    matrix4f mat;
    mat[0] = vector4f(f / cam.aspectRatio, 0, 0, 0);
    mat[1] = vector4f(0, f, 0, 0);
    mat[2] = vector4f(0, 0, m22, -1);
    mat[3] = vector4f(0, 0, m23, 0);

    return mat;
    }
}

void RenderManager::initialize()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    // Take care not to set camera near clipping plane to zero, that hyucks up projection and depth test
    Camera testCamera(vector3f(0, 5, 2), vector3f(0), 45, 0.01, 100, vector3f(0.6, 0.8, 1.0));
    testCamera.aspectRatio = 1920.0f / 1080.0f;
    testProjection = testCamera.projectionMatrix();
    testView = testCamera.viewMatrix();

    DEBUG << testProjection << "\n\n" << testView << "\n\n";

    DEBUG
        << testCamera.fieldOfView << "\n"
        << testCamera.nearClippingPlane << "\n"
        << testCamera.farClippingPlane << "\n"
        << testCamera.aspectRatio << "\n";
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

    for (const auto & dc : _drawCalls)
    {
        // todo sort : shader -> mesh -> entity
        auto & material = dc.material.get();
        auto & shader = material.shader.get();
        auto & mesh = dc.mesh.get();

        glUseProgram(shader.id);

        // per entity = drawCall
        glUniformMatrix4fv(shader.modelLocation, 1, GL_FALSE, &dc.model[0][0]);
        glUniformMatrix4fv(shader.modelITLocation, 1, GL_TRUE, &dc.inverse[0][0]);

        glBindVertexArray(mesh.vao);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material.texture);
        glUniform1i(shader.mainTextureLocation, 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material.tex1);
        glUniform1i(shader.normalMapLocation, 1);

        glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, nullptr);
    }

    _drawCalls.clear();
    glFinish();
}

void RenderManager::addDrawCall(const transform & tr, const renderer & r)
{
    _drawCalls.emplace_back(
        drawCall {
            modelMatrix(tr),
            inverseModelMatrix(tr),
            r.mesh,
            r.material
    });
}


void RenderManager::updateCamera(const CameraComponent & cam, const transform & tr)
{
    testView = viewMatrix(tr);
    testProjection = projectionMatrix(cam);

    static bool debugged = false;
    if (!debugged)
    {
        DEBUG << testProjection << "\n\n" << testView << "\n\n";

        DEBUG
            << cam.fieldOfView << "\n"
            << cam.nearClippingPlane << "\n"
            << cam.farClippingPlane << "\n"
            << cam.aspectRatio << "\n";

        debugged = true;
    }

}

void RenderManager::terminate() {}
