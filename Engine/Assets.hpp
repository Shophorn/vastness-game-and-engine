/*
LeoTamminen
Created 24/02/2019
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>

#include "Mesh.hpp"
#include "AssetLoader.hpp"
#include "Shader.hpp"
#include "DEBUG.hpp"


struct MeshAssetHandle
{
    int index = -1;
};

class MeshManager
{
public:
    using handle_type = MeshAssetHandle;

    MeshInstance get(handle_type handle) { return _instances[handle.index]; }
    handle_type instantiate (std::string path);
    handle_type instantiate (handle_type handle);

private:
    std::vector<MeshAsset>                  _assets{};
    std::vector<MeshInstance>               _instances{};
    std::unordered_map<std::string, int>    _loadedFileIndexes{};
    std::unordered_map<int, int>            _loadedAssetIndexes{};
};


namespace core
{
    inline MeshManager meshes{};
}

void setVertexAttributes(MeshInstance instance, Shader shader);
