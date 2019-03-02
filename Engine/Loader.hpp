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


//    struct textureLoadInfo
//    {
//        constexpr static int RGBA = 0;
//        constexpr static int RGB = 1;
//
//        std::string path;
//        int colorMode = RGBA;
//
//        std::string toString()
//        {
//            return "[" + path + ", mode: " + (colorMode == RGBA ? "RGBA" : colorMode == RGB ? "RGB" : "none") + "]";
//        }
//    };
//
//    GLuint LoadTextureRGBA(textureLoadInfo);
}


