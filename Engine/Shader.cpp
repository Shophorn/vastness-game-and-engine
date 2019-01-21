/*
Leo Tamminen
22/11/2018
*/

#include "Shader.hpp"
//#include <fstream>

#include <iostream>

#include "FileOperations.hpp"
namespace
{
    const char * shaderPath = "Engine/Shaders/";
    const char * vertexExtension = "_vertex.glsl";
    const char * fragmentExtension = "_fragment.glsl";

//    const char * ReadSourceFile(const char * path)
//    {
//        using namespace std;
//
//        ifstream file (path, ios::in | ios::binary);
//        if (!file.good()) return nullptr;
//
//        file.seekg(0, ios::end);
//        int length = file.tellg();
//        file.seekg(0, ios::beg);
//
//        char * source = new char [length + 1];
//
//        file.read(source, length);
//
//        source[length] = 0;
//
//        return source;
//    }

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
        const char * vertexSource = FileOperations::ReadFile(vertexPath.c_str());
        GLuint vertexShader = ShaderFromSource(vertexSource, GL_VERTEX_SHADER);
        DoPrintIfNotGood("vertex", vertexShader);

        // Fragement shader
        std::string fragmentPath = shaderPath + name + fragmentExtension;
        const char * fragmentSource = FileOperations::ReadFile(fragmentPath.c_str());
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

ShaderProgram ShaderProgram::Load(std::string shaderName)
{
    GLuint id = LoadShaderWithName(shaderName);
    return ShaderProgram(id);
}
