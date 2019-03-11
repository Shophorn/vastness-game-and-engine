/*
Shophorn Games
Leo Tamminen
Created 28/02/2019
*/

#pragma once

#include <string>
#include <unordered_map>

#include "../Serialization.hpp"
#include "../Mesh.hpp"

struct meshHandle
{
    int index;
    MeshInstance & get() const;
};

class MeshManager
{
    struct info
    {
        meshHandle handle;
        std::string path;
    };

    using name_type = std::string;

    std::unordered_map<std::string, info> _nameInfoMap{};
    std::vector<MeshInstance> _instances;
    std::vector< MeshData *> _loadedAssets{};
    std::unordered_map<name_type, int> _loadedFileIndexes{};
    std::unordered_map<int, int> _loadedAssetIndexes{};
    std::unordered_map<int, name_type> _handleNameMap{};
public:
    void addLoadInfo(const serialization::Value & value);
    meshHandle instantiate(std::string name);
    meshHandle instantiate(meshHandle handle);

    // use handle - 1, since it is just int now, but we still want to keep handle 0 invalid
    MeshInstance & get (meshHandle  handle) { return _instances[handle.index]; }
};

namespace resources
{
    inline MeshManager meshes;
}
