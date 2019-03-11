#pragma once

#include <GL/glew.h>
#include <string>
#include <array>

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
    
    GLint mainTextureLocation   = -1;
    GLint normalMapLocation     = -1;

    Shader () = default;

    static Shader create(const std::string & vertexPath, const std::string & fragmentPath);

private:

    explicit Shader (GLuint _id) :
        id (_id),
        viewLocation        (glGetUniformLocation(id, "view")),
        projectionLocation  (glGetUniformLocation(id, "projection")),
        modelLocation       (glGetUniformLocation(id, "model")),
        modelITLocation     (glGetUniformLocation(id, "model_it")),
        lightDirLocation    (glGetUniformLocation(id, "lightDir")),
        lightColorLocation  (glGetUniformLocation(id, "_LightColor")),
        cameraPosLocation   (glGetUniformLocation(id, "cameraPos")),

        mainTextureLocation (glGetUniformLocation(id, "_AlbedoTexture")),
        normalMapLocation   (glGetUniformLocation(id, "_NormalTexture"))
    {}
};