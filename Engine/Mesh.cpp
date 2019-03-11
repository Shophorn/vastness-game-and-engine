#include <fstream>
#include <sstream>
#include <cassert>

#include "Rendering/Shader.hpp"
#include "Mesh.hpp"
#include "Stopwatch.hpp"
#include "DEBUG.hpp"


namespace detail
{
    template<typename T>
    void generateBuffer(GLenum bufferType, GLuint *target, const std::vector<T> &data)
    {
        static std::vector<float> fuckVector {0.5f, 4.5f, 2.3f, 4.5f};

        glGenBuffers(1, target);
        glBindBuffer(bufferType, *target);
        glBufferData(bufferType, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    }
}

MeshInstance instantiate(MeshData * asset)
{
    assert(!asset->vertices.empty() && !asset->elements.empty() && "invalid mesh");

    MeshInstance instance{};
    glGenVertexArrays(1, &instance.vao);
    glBindVertexArray(instance.vao);

    detail::generateBuffer(GL_ARRAY_BUFFER, &instance.verticesBO, asset->vertices);
    detail::generateBuffer(GL_ELEMENT_ARRAY_BUFFER, &instance.elementsBO, asset->elements);

    if (!asset->texcoords.empty())
        detail::generateBuffer(GL_ARRAY_BUFFER, &instance.texcoordBO, asset->texcoords);

    if (!asset->normals.empty())
        detail::generateBuffer(GL_ARRAY_BUFFER, &instance.normalsBO, asset->normals);

    instance.elementCount = static_cast<GLsizei>(asset->elements.size());

    return instance;
}


