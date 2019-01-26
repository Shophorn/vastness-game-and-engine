/*
Leo Tamminen
Created 27/12/2018
*/

#pragma once
#include <string>

#include "Scene.hpp"
#include "Screen.hpp"

namespace Engine::SceneLoader
{
    Screen LoadContext(const char * path);
    Scene Load(const char * path);
}