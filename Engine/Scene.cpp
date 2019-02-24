/*
LeoTamminen
Created 21/01/2019
*/

#include "Scene.hpp"

void Core::Scene::LoadShaderIfNotLoader(std::string shaderName)
{
    if (shaders.find(shaderName) == shaders.end())
    {
        shaders.insert_or_assign(shaderName, Shader::Load(shaderName));

        if (shaderName == "sprite")
        {
            GLuint id  = shaders[shaderName].id;
            glUseProgram(id);

            glUniform1i(glGetUniformLocation(id, "animationRows"), 1);
            glUniform1i(glGetUniformLocation(id, "animationColumns"), 2);
            glUniform1i(glGetUniformLocation(id, "animationFrames"), 2);
            glUniform1i(glGetUniformLocation(id, "animationIndex"), 0);
            glUniform1f(glGetUniformLocation(id, "frameRate"), 2.0f);
        }
    }
}
