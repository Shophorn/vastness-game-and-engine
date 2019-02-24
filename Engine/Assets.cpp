/*
LeoTamminen
Created 25/02/2019
*/

#include "Assets.hpp"

namespace detail
{
    template<typename T>
    void generateBuffer(GLenum bufferType, GLuint *target, const std::vector<T> &data)
    {
        glGenBuffers(1, target);
        glBindBuffer(bufferType, *target);
        glBufferData(bufferType, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    }

    MeshInstance instantiate(MeshAsset asset)
    {
        assert(!asset.vertices.empty() && !asset.elements.empty() && "invalid mesh");

        MeshInstance instance{};
        glGenVertexArrays(1, &instance.vao);
        glBindVertexArray(instance.vao);

        GLenum GLDrawMode = GL_STATIC_DRAW;

        generateBuffer(GL_ARRAY_BUFFER, &instance.verticesBO, asset.vertices);
        generateBuffer(GL_ELEMENT_ARRAY_BUFFER, &instance.elementsBO, asset.elements);

        if (!asset.texcoords.empty())
            generateBuffer(GL_ARRAY_BUFFER, &instance.texcoordBO, asset.texcoords);

        if (!asset.normals.empty())
            generateBuffer(GL_ARRAY_BUFFER, &instance.normalsBO, asset.normals);

        instance.elementCount = static_cast<GLsizei>(asset.elements.size());

        return instance;
    }

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

    _instances.emplace_back(detail::instantiate(_assets[assetIndex]));
    int instanceIndex = (int)_instances.size() - 1;
    _loadedAssetIndexes.emplace(instanceIndex, assetIndex);

    handle_type handle { instanceIndex };
    return handle;
}

MeshManager::handle_type MeshManager::instantiate(MeshManager::handle_type handle)
{
    int assetIndex = _loadedAssetIndexes[handle.index];
    _instances.emplace_back(detail::instantiate(_assets[assetIndex]));

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
