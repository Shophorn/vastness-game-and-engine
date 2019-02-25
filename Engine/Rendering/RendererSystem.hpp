/*
Shophorn
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>
#include "RenderManager.hpp"
#include "../ECS.hpp"
#include "../Assets.hpp"

struct transform;
struct renderer
{
    GLuint texture;
    int shaderHandle;
    InstanceHandle<MeshInstance> meshHandle;
};

struct rendererSystem
{
    using components = mtl::List<transform, renderer>;

    void update(const transform & tr, const renderer & r)
    {
        core::renderManager.addRenderer(tr, r);
    }
};