/*
Leo Tamminen
22/11/2018.
*/

#pragma once

#include "Mesh.hpp"

namespace loader
{
    bool LoadMeshAsset(const char *path, Mesh *target);
    Mesh * LoadOBJPtr(const char *path);

    bool LoadTextureRGB(const char *path, GLuint *target);
    bool LoadTextureRGBA(const char *path, GLuint *target);

    template <typename Asset>
    Asset load(std::string path);


};


