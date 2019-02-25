/*
LeoTamminen
Created 24/02/2019
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Loader.hpp"

template<typename Instance, typename Asset>
Instance instantiate(Asset asset);

template <typename T>
struct InstanceHandle
{
    int index = -1;
};

template <typename Instance, typename Asset>
class AssetManager
{
public:
    using handle_type = InstanceHandle<Instance>;

    Instance get (handle_type handle){ return _instances[handle.index]; }
    handle_type instantiate (std::string path)
    {
        int assetIndex = -1;
        if (_loadedFileIndexes.find(path) == _loadedFileIndexes.end())
        {
            assetIndex = (int)_assets.size();
            _assets.emplace_back(loader::load<Asset>(path));
            _loadedFileIndexes.emplace(path, assetIndex);
        }
        else
        {
            assetIndex = _loadedFileIndexes[path];
        }

        Asset asset = _assets[assetIndex];
        _instances.emplace_back(::instantiate<Instance, Asset>(asset));
        int instanceIndex = (int)_instances.size() - 1;
        _loadedAssetIndexes.emplace(instanceIndex, assetIndex);

        handle_type handle { instanceIndex };
        return handle;
    }

    handle_type instantiate (handle_type handle)
    {
        int assetIndex = _loadedAssetIndexes[handle.index];
        _instances.emplace_back(::instantiate<Instance, Asset>(_assets[assetIndex]));

        handle_type newHandle { (int)_instances.size() - 1 };
        return newHandle;
    }

private:
    std::vector<Asset>                      _assets{};
    std::vector<Instance>                   _instances{};
    std::unordered_map<std::string, int>    _loadedFileIndexes{};
    std::unordered_map<int, int>            _loadedAssetIndexes{};
};



