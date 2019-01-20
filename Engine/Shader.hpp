#pragma once

#include <GL/glew.h>
#include <string>

struct ShaderProgram
{
public:
    GLuint id = 0;

    GLint viewLocation          = -1;
    GLint projectionLocation    = -1;
    GLint modelLocation         = -1;
    GLint modelITLocation       = -1;
    GLint lightDirLocation      = -1;
    GLint cameraPosLocation     = -1;

    ShaderProgram () = default;

    explicit ShaderProgram (GLuint _id) :
        id (_id),
        viewLocation        (glGetUniformLocation(id, "view")),
        projectionLocation  (glGetUniformLocation(id, "projection")),
        modelLocation       (glGetUniformLocation(id, "model")),
        modelITLocation     (glGetUniformLocation(id, "model_it")),
        lightDirLocation    (glGetUniformLocation(id, "lightDir")),
        cameraPosLocation   (glGetUniformLocation(id, "cameraPos"))
    {}

    void Use() const { glUseProgram(id); }

    static ShaderProgram Load(std::string shaderName);
};