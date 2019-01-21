/*
Leo Tamminen
Created 27/12/2018
*/

#pragma once

#include "Scene.hpp"
#include <string>

namespace Engine::SceneLoader
{
    Scene Load(std::string path);
}