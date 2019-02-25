#pragma once

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <cassert>

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

MeshInstance instantiate(MeshAsset asset);

namespace convert
{
    MeshAsset * fromOBJ(std::ifstream &&file);
}