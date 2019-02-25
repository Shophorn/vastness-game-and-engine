/*
Leo Tamminen
22/11/2018.
*/

#pragma once

#include <GL/glew.h>
#include <string>

namespace loader
{
    template <typename Asset>
    Asset load(const std::string &path);

    bool LoadTextureRGB(const char *path, GLuint *target);
    bool LoadTextureRGBA(const char *path, GLuint *target);
}


