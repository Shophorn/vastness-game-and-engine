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

    mshader->Use();

    glUniformMatrix4fv(mshader->modelLocation, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(mshader->modelLocation, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(mshader->modelITLocation, 1, GL_FALSE, &modelIT[0][0]);

    if (animator != nullptr)
    {
        animator->SetShaderValues();
        glUniform1i (glGetUniformLocation(mshader->id, "isAnimated"), 1);
    }
    else
    {
        glUniform1i (glGetUniformLocation(mshader->id, "isAnimated"), 0);
    }

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}
