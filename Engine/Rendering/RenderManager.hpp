/*
Shophorn Games
Leo Tamminen
Created 16/02/2019
*/

#pragma once

#include <GL/glew.h>
#include <vector>
#include <unordered_map>
#include "../Shader.hpp"
#include "../Maths/Maths.hpp"

struct transform;
struct renderer;

struct renderData
{
    matrix4f model{};
    matrix4f inverse{};
    unsigned shader{};
};

class RenderManager
{
private:
    std::vector<renderData> _toRender{};
    std::vector<shader> _shaders{};
public:
    RenderManager() = default;
    ~RenderManager() = default;

    void initialize();
    void terminate();
    void render();

    void addRenderer(const transform &, const renderer &);
};

namespace core
{
    extern RenderManager renderManager;
}

