#pragma once

#include <GL/glew.h>
#include <vector>

struct Shader;

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

MeshInstance instantiate(MeshData * data);
