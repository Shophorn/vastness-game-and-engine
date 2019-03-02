#include <fstream>
#include <sstream>
#include <cassert>

#include "ResourceManager.hpp"
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

namespace detail
{
    void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
    {
        glBindBuffer(GL_ARRAY_BUFFER, target);
        auto location = glGetAttribLocation(shader, name.c_str());
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
    }

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

