/*
Shophorn Games
Leo Tamminen
Created 16/02/2019
*/

#pragma once

#include <GL/glew.h>
#include <vector>
#include <unordered_map>

struct transform;

class RenderManager
{
private:

public:
    RenderManager() = default;
    ~RenderManager() = default;

    void initialize();
//    void terminate();

    void render();

    void addTarget(transform&);
};

namespace core
{
    extern RenderManager renderManager;
}

