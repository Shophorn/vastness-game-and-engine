/*
Shophorn
Leo Tamminen
Created 26/12/2018
*/

#include "Renderer.hpp"
#include <iostream>

using namespace Core;

void Renderer::Draw()
{
    auto model = transform.modelMatrixNew();
    auto modelIT = transform.inverseModelMatrix();
    modelIT.transpose();
//    auto modelIT = glm::transpose(glm::inverse(transform.modelMatrix()));

    shader->Use();

    glUniformMatrix4fv(shader->modelLocation, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(shader->modelLocation, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(shader->modelITLocation, 1, GL_FALSE, &modelIT[0][0]);

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
