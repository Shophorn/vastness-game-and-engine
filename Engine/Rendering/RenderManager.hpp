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
    
    void registerLight(light l);

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

    static constexpr int MAX_DIRECTIONAL_LIGHTS = 2;
    int currentLightCount = 0;
    std::array<light, MAX_DIRECTIONAL_LIGHTS> _directionalLights;
};

namespace core
{
    extern RenderManager renderManager;
}

