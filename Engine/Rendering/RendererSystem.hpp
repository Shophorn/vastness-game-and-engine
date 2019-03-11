/*
Shophorn Games
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>
#include "../ECS.hpp"
#include "../TransformComponent.hpp"

#include "../Resources/Textures.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"
#include "../Resources/Materials.hpp"

#include "RenderManager.hpp"

struct renderer
{
    meshHandle      mesh {};
    MaterialHandle  material {};
};

struct rendererSystem
{
    using components = mpl::List<transform, renderer>;
    
    void update(const transform & tr, const renderer & r)
    {
        core::renderManager.addDrawCall(tr, r);
    }
};