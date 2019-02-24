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
    GLuint vao{};
    GLuint texture{};
    int elementCount{};
    int shaderHandle{};

};

class RenderManager
{
private:
    std::vector<renderData> _toRender{};
    std::vector<Shader> _shaders{};
    std::unordered_map<std::string, signed> _shaderMap {};

public:
    RenderManager() = default;
    ~RenderManager() = default;

    void initialize();
    void terminate();
    void render();

    void addRenderer(const transform &, const renderer & r);

    int getShaderHandle(const std::string & name);
    const Shader & getShader(int handle) { return _shaders[handle]; }
    const Shader & getShader (const std::string & name) { return _shaders[_shaderMap[name]]; }
};

namespace core
{
    extern RenderManager renderManager;
}

