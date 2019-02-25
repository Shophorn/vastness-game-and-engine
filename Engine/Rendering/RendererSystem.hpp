/*
Shophorn
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>
#include "RenderManager.hpp"
#include "../ECS.hpp"
#include "../ResourceManager.hpp"

struct transform;
struct renderer
{
    GLuint texture{};
    int shaderHandle{};
    mesh_handle mesh{};

    renderer(GLuint _texture, int _shaderHandle, mesh_handle _mesh) :
        texture(_texture), shaderHandle(_shaderHandle), mesh (_mesh) {
        debug << texture << ", " << shaderHandle << ", " << mesh.index << "\n";
    }
};

struct rendererSystem
{
    using components = mtl::List<transform, renderer>;

    void update(const transform & tr, const renderer & r)
    {
        core::renderManager.addRenderer(tr, r);
    }
};