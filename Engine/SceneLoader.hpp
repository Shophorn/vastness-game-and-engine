/*
Leo Tamminen
Created 27/12/2018
*/

#pragma once
#include <string>

#include "Scene.hpp"
#include "Screen.hpp"

#include <vector>

namespace Core::SceneLoader
{
    Screen LoadContext(const char * path);
    Scene Load(const char * path);
}