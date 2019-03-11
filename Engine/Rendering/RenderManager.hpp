/*
Shophorn Games
Leo Tamminen
Created 16/02/2019
*/

#pragma once

#include <GL/glew.h>
#include <vector>
#include <array>
#include <unordered_map>

#include "Light.hpp"
#include "../Maths/Maths.hpp" // only for drawCall
#include "../Resources/Meshes.hpp"
#include "../Resources/Materials.hpp"
struct transform;
struct renderer;

class RenderManager
{
public:
    RenderManager() = default;
    ~RenderManager() = default;

    void initialize();
    void terminate();
    void render();

    void addDrawCall(const transform &, const renderer &r);
    LightingManager lighting;

private:
    struct drawCall
    {
        matrix4f model{};
        matrix4f inverse{};
        GLuint texture{};
        int shader;
        meshHandle mesh;
    };

    std::vector<drawCall> _drawCalls{};

    std::vector<Light> _staticLights {};
};

namespace core
{
    extern RenderManager renderManager;
}

