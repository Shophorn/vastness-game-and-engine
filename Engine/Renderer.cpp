/*
Shophorn
Leo Tamminen
Created 26/12/2018
*/

#include "Renderer.hpp"

using namespace Engine;

void Renderer::Draw()
{
    auto model = transform.modelMatrix();

    glm::mat4 modelIT = glm::transpose(glm::inverse(model));

    shader->Use();

    glUniformMatrix4fv(shader->modelLocation, 1, false, &model[0][0]);
    glUniformMatrix4fv(shader->modelITLocation, 1, false, &modelIT[0][0]);

    if (animator != nullptr)
    {
        animator->SetShaderValues();
        glUniform1i (glGetUniformLocation(shader->id, "isAnimated"), 1);
    }
    else
    {
        glUniform1i (glGetUniformLocation(shader->id, "isAnimated"), 0);
    }

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}
