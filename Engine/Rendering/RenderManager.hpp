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
#include "../Maths/Maths.hpp" // only for renderdata
#include "../Resources/Meshes.hpp"

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

    struct renderHandle
    {
        int shader;
        meshHandle mesh;
    };

    renderHandle bindRenderInfo(int shader, meshHandle mesh);

    LightingManager lighting;

private:
    struct renderData
    {
        matrix4f model{};
        matrix4f inverse{};
        GLuint texture{};
        renderHandle handle{};
    };

    std::vector<renderData> _toRender{};
    std::vector<renderHandle> _renderHandles{};

    std::vector<Light> _staticLights {};
};

namespace core
{
    extern RenderManager renderManager;
}

