/*
Leo Tamminen
22/11/2018
*/

#include "Shader.hpp"
#include "../FileOperations.hpp"

namespace
{
    GLuint ShaderFromSource(const char * source, GLenum SHADER_TYPE)
    {
        GLuint shaderID = glCreateShader(SHADER_TYPE);
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
}// Anon namespace


Shader Shader::create(const std::string & vertexPath, const std::string & fragmentPath)
{
        auto vertexSource = fileOps::ReadFile(vertexPath);
        GLuint vertexShader = ShaderFromSource(vertexSource.c_str(), GL_VERTEX_SHADER);
        DoPrintIfNotGood("vertex", vertexShader);

        auto fragmentSource = fileOps::ReadFile(fragmentPath);
        GLuint fragmentShader = ShaderFromSource(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
        DoPrintIfNotGood("fragment", fragmentShader);

        GLuint id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glBindFragDataLocation(id, 0, "outColor");

        glLinkProgram(id);

        return Shader(id);
}