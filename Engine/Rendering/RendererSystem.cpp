/*
Shophorn games
Leo Tamminen
Created 11/03/2019
*/
#include "RendererSystem.hpp"
#include "../Serialization.hpp"

namespace
{
    void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
    {
        glBindBuffer(GL_ARRAY_BUFFER, target);
        auto location = glGetAttribLocation(shader, name.c_str());
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
    }

    void setVertexAttributes(MeshInstance instance, Shader shader)
    {
        glBindVertexArray(instance.vao);

        setAttribPointer(instance.verticesBO, 3, shader.id, "position");

        if (instance.texcoordBO > 0 )
            setAttribPointer(instance.texcoordBO, 2, shader.id, "texcoord");

        if (instance.normalsBO > 0 )
            setAttribPointer(instance.normalsBO, 3, shader.id, "normal");

    }
}

namespace serialization
{
    template <>
    renderer deserialize<renderer>(const Value & value)
    {
        auto meshHandle         = resources::meshes.instantiate(value["mesh"].GetString());
        auto materialHandle     = resources::materials.getHandle(value["material"].GetString());
        auto shaderHandle       = materialHandle.get().shader;

        setVertexAttributes(meshHandle.get(), shaderHandle.get());
        return renderer{ meshHandle, materialHandle };
    }
}