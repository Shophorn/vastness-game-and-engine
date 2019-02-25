#pragma once

#include <GL/glew.h>
#include <vector>
#include "ResourceManager.hpp"
#include "Shader.hpp"

struct MeshData
{
    std::vector<float> vertices{};
    std::vector<float> normals{};
    std::vector<float> texcoords{};
    std::vector<unsigned> elements{};
};

struct MeshInstance
{
    GLuint vao{};

    GLuint verticesBO{};
    GLuint elementsBO{};
    GLuint normalsBO{};
    GLuint texcoordBO{};

    GLsizei elementCount {};
};

using mesh_handle = InstanceHandle<MeshInstance>;

namespace core
{
    inline ResourceManager<MeshInstance, MeshData> meshes{};
}

void setVertexAttributes(MeshInstance instance, Shader shader);



