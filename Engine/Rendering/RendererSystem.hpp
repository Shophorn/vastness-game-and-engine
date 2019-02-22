/*
Shophorn
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>

#include "RenderManager.hpp"

#include "../ECS.hpp"
#include "../TransformComponent.hpp"

#include "../DEBUG.hpp"

struct renderer
{
    GLuint vao;
    GLuint texture;
    GLuint shaderId;
    GLuint shaderValueBuffer;
};

struct rendererSystem
{
    using components = mtl::List<transform, renderer>;

    rendererSystem()
    {
        cout << "renderer system constructor\n";
    }

    void update(transform & tr, renderer & r)
    {
//        cout << "rendering somthing\n";
        core::renderManager.addTarget(tr);
    }
};