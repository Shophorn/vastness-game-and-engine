/*
LeoTamminen
Created 25/02/2019
*/

#include "Assets.hpp"
#include "Mesh.hpp"

namespace detail
{
    // todo: somewhere else
    void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
    {
        glBindBuffer(GL_ARRAY_BUFFER, target);
        auto location = glGetAttribLocation(shader, name.c_str());
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
    }

}

 MeshManager::handle_type MeshManager::instantiate(std::string path)
{
    int assetIndex = -1;
    if (_loadedFileIndexes.find(path) == _loadedFileIndexes.end())
    {
        assetIndex = (int)_assets.size();
        _assets.emplace_back(loader::load<MeshAsset>(path));
        _loadedFileIndexes.emplace(path, assetIndex);
    }
    else
    {
        assetIndex = _loadedFileIndexes[path];
    }

    MeshAsset asset = _assets[assetIndex];
    _instances.emplace_back(::instantiate(asset));
    int instanceIndex = (int)_instances.size() - 1;
    _loadedAssetIndexes.emplace(instanceIndex, assetIndex);

    handle_type handle { instanceIndex };
    return handle;
}

MeshManager::handle_type MeshManager::instantiate(MeshManager::handle_type handle)
{
    int assetIndex = _loadedAssetIndexes[handle.index];
    _instances.emplace_back(::instantiate(_assets[assetIndex]));

    handle_type newHandle { (int)_instances.size() - 1 };
    return newHandle;
}


void setVertexAttributes(MeshInstance instance, Shader shader)
{
    glBindVertexArray(instance.vao);

    using namespace detail;
    setAttribPointer(instance.verticesBO, 3, shader.id, "position");

    if (instance.texcoordBO > 0 )
        setAttribPointer(instance.texcoordBO, 2, shader.id, "texcoord");

    if (instance.normalsBO > 0 )
        setAttribPointer(instance.normalsBO, 3, shader.id, "normal");

}
