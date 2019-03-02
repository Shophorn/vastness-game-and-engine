/*
LeoTamminen
Created 28/02/2019
*/

#include "Meshes.hpp"
#include "../Loader.hpp"
#include "../Mesh.hpp"
#include "../DEBUG.hpp"

void Meshes::addLoadInfo(const serialization::Value &value)
{
    auto jsonArray = value.GetArray();
    for (const auto & item : jsonArray)
    {
        auto obj = item.GetObject();
        auto name = obj["name"].GetString();
        auto path = obj["path"].GetString();
        _nameInfoMap.emplace(name, info{0, path});
    }
}

meshHandle Meshes::instantiate(std::string name)
{
    int assetIndex;
    if (_loadedFileIndexes.find(name) == _loadedFileIndexes.end())
    {
        assetIndex = (int)_loadedAssets.size();
        auto path = _nameInfoMap[name].path;
        _loadedAssets.emplace_back(new MeshData(loader::load<MeshData>(path)));
        _loadedFileIndexes.emplace(name, assetIndex);
    }
    else
    {
        assetIndex = _loadedFileIndexes[name];
    }

    MeshData * asset = _loadedAssets[assetIndex];
    _data.emplace_back(::instantiate(asset));

    int instanceIndex = (int)_data.size();
    _loadedAssetIndexes.emplace(instanceIndex, assetIndex);

    return instanceIndex;
}
