/*
LeoTamminen
Created 26/12/2018
*/

#include "Renderer.hpp"
#include "VectorsAndMatrices.hpp"

using namespace Engine;

void Renderer::Draw()
{
    mat4 model = transform.modelMatrix();
    glm::mat3 modelIT = glm::transpose(glm::inverse(model));

    shader->Use();

    glUniformMatrix4fv(shader->modelLocation, 1, false, &model[0][0]);
    glUniformMatrix3fv(shader->modelITLocation, 1, false, &modelIT[0][0]);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
}
