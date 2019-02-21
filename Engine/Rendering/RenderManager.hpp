/*
Shophorn Games
Leo Tamminen
Created 16/02/2019
*/

#pragma once

#include <vector>

class RenderManager
{
private:

public:
    RenderManager() = default;
    ~RenderManager() = default;

    void initialize();
//    void terminate();

    void render();
};

namespace core
{
    extern RenderManager renderManager;
}

