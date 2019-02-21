/*
Shophorn
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>

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

struct renderingSystem
{
    using components = mtl::List<transform, renderer>;

    void update(transform & tr, renderer & r)
    {
        cout << "rendering somthing\n";
    }
};