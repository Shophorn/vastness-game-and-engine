#pragma once

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <cassert>
#include "Assets.hpp"
#include "Shader.hpp"

struct MeshAsset
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

namespace convert
{
    MeshAsset * fromOBJ(std::ifstream &&file);
}

namespace core
{
    inline AssetManager<MeshInstance, MeshAsset> meshes{};
}

void setVertexAttributes(MeshInstance instance, Shader shader);
