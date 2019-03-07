#pragma once

#include <GL/glew.h>
#include <string>

struct Shader
{
public:
    GLuint id = 0;

    GLint viewLocation          = -1;
    GLint projectionLocation    = -1;
    GLint modelLocation         = -1;
    GLint modelITLocation       = -1;
    GLint lightDirLocation      = -1;
    GLint lightColorLocation    = -1;
    GLint cameraPosLocation     = -1;

    Shader () = default;

    explicit Shader (GLuint _id) :
        id (_id),
        viewLocation        (glGetUniformLocation(id, "view")),
        projectionLocation  (glGetUniformLocation(id, "projection")),
        modelLocation       (glGetUniformLocation(id, "model")),
        modelITLocation     (glGetUniformLocation(id, "model_it")),
        lightDirLocation    (glGetUniformLocation(id, "lightDir")),
        lightColorLocation  (glGetUniformLocation(id, "_LightColor")),
        cameraPosLocation   (glGetUniformLocation(id, "cameraPos"))
    {}

    static Shader Load(std::string shaderName);
};