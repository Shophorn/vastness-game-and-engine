/*
Leo Tamminen
22/11/2018
*/

#include "Shader.hpp"
#include <iostream>

#include "../FileOperations.hpp"
namespace
{
    const char * shaderPath = "Engine/Shaders/";
    const char * vertexExtension = "_vertex.glsl";
    const char * fragmentExtension = "_fragment.glsl";

    GLuint ShaderFromSource(const char * source, GLenum type)
    {
        GLuint shaderID = glCreateShader(type);
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        return shaderID;
    }


    void DoPrintIfNotGood(const char * label, GLuint shader)
    {
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            char logBuffer [500];
            glGetShaderInfoLog(shader, 500, nullptr, logBuffer);
            printf("Shader compile failed (%s):\n%s\n", label, logBuffer);
        }

    }

    GLuint LoadShaderWithName(std::string name)
    {
        // Vertex shader
        std::string vertexPath = shaderPath + name + vertexExtension;
        const char * vertexSource = fileOps::ReadFile(vertexPath.c_str());
        GLuint vertexShader = ShaderFromSource(vertexSource, GL_VERTEX_SHADER);
        DoPrintIfNotGood("vertex", vertexShader);

        // Fragement shader
        std::string fragmentPath = shaderPath + name + fragmentExtension;
        const char * fragmentSource = fileOps::ReadFile(fragmentPath.c_str());
        GLuint fragmentShader = ShaderFromSource(fragmentSource, GL_FRAGMENT_SHADER);
        DoPrintIfNotGood("fragment", fragmentShader);

        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glBindFragDataLocation(shaderProgram, 0, "outColor");
        glLinkProgram(shaderProgram);

        delete [] vertexSource;
        delete [] fragmentSource;

        return shaderProgram;
    }

}// Anon namespace

Shader Shader::Load(std::string shaderName)
{
    GLuint id = LoadShaderWithName(shaderName);
    return Shader(id);
}
