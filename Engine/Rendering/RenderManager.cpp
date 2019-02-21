/*
LeoTamminen
Created 16/02/2019
*/

#include <GL/glew.h>
#include <iostream>

#include "RenderManager.hpp"

RenderManager core::renderManager;

void RenderManager::initialize()
{
    glClearColor(0.2, 0.2, 0.9, 1.0);
}

void RenderManager::render()
{
//    std::cout << "rendering\n";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glFinish();
}

