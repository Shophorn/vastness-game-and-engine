/*
Shophorn Games
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>
#include "RenderManager.hpp"
#include "../ECS.hpp"

struct renderer
{
    GLuint texture{};
    RenderManager::renderHandle handle{};
};

struct rendererSystem
{
    using components = mpl::List<transform, renderer>;
    void update(const transform & tr, const renderer & r)
    {
        core::renderManager.addDrawCall(tr, r);
    }
};

#include "../Serialization.hpp"
#include "../Resources/Textures.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"

#include "../DEBUG.hpp"

namespace serialization
{
    template <>
    inline renderer deserialize<renderer>(const Value & value)
    {
        auto tex        = resources::textures.getHandle(value["texture"].GetString());
        auto shader     = resources::shaders.getHandle(value["shader"].GetString());
        auto mesh       = resources::meshes.instantiate(value["mesh"].GetString());

        auto renderHandle = core::renderManager.bindRenderInfo(shader, mesh);
        return renderer{ tex, renderHandle };
    }
}
