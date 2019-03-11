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


class MeshManager
{
public:
    struct Handle
    {   
        int index;
        MeshInstance & get() const;
    };

    void addLoadInfo(const serialization::Value & value);
    Handle instantiate(std::string name);
    Handle instantiate(Handle handle);
    
private:
    struct info
    {
        Handle handle;
        std::string path;
    };

    using name_type = std::string;

    std::unordered_map<std::string, info> _nameInfoMap{};
    std::vector<MeshInstance> _instances;
    std::vector< MeshData *> _loadedAssets{};
    std::unordered_map<name_type, int> _loadedFileIndexes{};
    std::unordered_map<int, int> _loadedAssetIndexes{};
    std::unordered_map<int, name_type> _handleNameMap{};
};

using meshHandle = MeshManager::Handle;

namespace resources
{
    inline MeshManager meshes;
}
