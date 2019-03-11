/*
Shophorn Games
Leo Tamminen
Created 21/02/2019
*/

#pragma once

#include <GL/glew.h>
#include "RenderManager.hpp"
#include "../ECS.hpp"
#include "Light.hpp"

struct renderer
{
    GLuint texture{};
    // RenderManager::renderHandle handle{};
    meshHandle mesh;
    int shader;
};

struct rendererSystem
{
    using components = mpl::List<transform, renderer>;
    void update(const transform & tr, const renderer & r)
    {
        core::renderManager.addDrawCall(tr, r);
    }
};

#include "../Serialization.hpp"
#include "../Resources/Textures.hpp"
#include "../Resources/Shaders.hpp"
#include "../Resources/Meshes.hpp"

#include "../DEBUG.hpp"

void setVertexAttributes(MeshInstance instance, Shader shader);


namespace serialization
{
    template <>
    inline renderer deserialize<renderer>(const Value & value)
    {
        auto tex        = resources::textures.getHandle(value["texture"].GetString());
        auto shader     = resources::shaders.getHandle(value["shader"].GetString());
        auto mesh       = resources::meshes.instantiate(value["mesh"].GetString());
        auto material   = 0; 
        if (value.HasMember("material"))
            material = resources::materials.getHandle(value["material"].GetString());

        setVertexAttributes(resources::meshes.get(mesh), resources::shaders.get(shader));
        return renderer{ tex, mesh, shader };//renderHandle };
    }
}



namespace detail
{
    inline void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
    {
        glBindBuffer(GL_ARRAY_BUFFER, target);
        auto location = glGetAttribLocation(shader, name.c_str());
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
    }

}
inline void setVertexAttributes(MeshInstance instance, Shader shader)
{
    glBindVertexArray(instance.vao);

    using namespace detail;
    setAttribPointer(instance.verticesBO, 3, shader.id, "position");

    if (instance.texcoordBO > 0 )
        setAttribPointer(instance.texcoordBO, 2, shader.id, "texcoord");

    if (instance.normalsBO > 0 )
        setAttribPointer(instance.normalsBO, 3, shader.id, "normal");

}
