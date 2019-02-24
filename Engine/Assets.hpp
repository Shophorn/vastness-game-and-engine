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

template <typename T>
class AssetManager
{
    using asset_type = T;
    std::unordered_map<std::string, asset_type> _assets;

public:
    bool hasLoadedAsset(std::string path)
    {
        return _assets.find(path) != _assets.end();
    }

    void load(std::string path)
    {
        if (hasLoadedAsset(path))
            return;
        _assets.emplace(path, loader::load<T>(path));
    }

    const T & get(std::string path)
    {
        assert(_assets.find(path) != _assets.end());
        return _assets[path];
    }
};


template <typename T>
inline void generateBuffer(GLenum bufferType, GLuint * target, const std::vector<T> & data)
{
    glGenBuffers(1, target);
    glBindBuffer(bufferType, *target);
    glBufferData(bufferType, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}

inline MeshInstance instantiate(MeshAsset asset)
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

inline void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
{
    glBindBuffer(GL_ARRAY_BUFFER, target);
    auto location = glGetAttribLocation(shader, name.c_str());
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
}

inline void setVertexAttributes(MeshInstance instance, Shader shader)
{
    glBindVertexArray(instance.vao);

    setAttribPointer(instance.verticesBO, 3, shader.id, "position");

    if (instance.texcoordBO > 0 )
        setAttribPointer(instance.texcoordBO, 2, shader.id, "texcoord");

    if (instance.normalsBO > 0 )
        setAttribPointer(instance.normalsBO, 3, shader.id, "normal");

}

namespace core
{
    inline AssetManager<MeshAsset> meshAssets{};
}

class MeshInstanceManager
{
    using handle_type = int;
    std::unordered_map<std::string, handle_type> _pathMap;
    std::vector<MeshInstance> _instances;

public:
    handle_type getHandle(const std::string & path)
    {
        if (_pathMap.find(path) == _pathMap.end())
        {

            _instances.emplace_back(instantiate(core::meshAssets.get(path)));
        }

        return _pathMap[path];
    }

    const MeshInstance & get(handle_type handle)
    {
        return _instances[handle];
    }

};

namespace core
{
    inline MeshInstanceManager meshInstances{};
}
