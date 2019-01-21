/*
LeoTamminen
Created 26/12/2018
*/

#pragma once

#include <GL/glew.h>

#include "Transform.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace Engine
{
    class Renderer
    {
    public:
        Transform transform;
        GLuint vao;
        GLuint texture;
        int elementCount;

        // Shared, don't delete
        ShaderProgram * shader = nullptr;

        // Owned, do delete
        Mesh * mesh = nullptr;

        Renderer () {}

        ~Renderer()
        {
            delete mesh;
        }

        Renderer(Transform _transform, GLuint _texture, Mesh * _mesh, ShaderProgram * _shader)
        {
            transform = _transform;
            texture = _texture;
            vao = _mesh->vao();
            elementCount = _mesh->elementCount();
            shader = _shader;

            mesh = _mesh;
        }

        void Draw();
    };
}