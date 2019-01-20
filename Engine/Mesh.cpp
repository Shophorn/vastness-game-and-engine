/*
Leo Tamminen
22/11/2018.
*/

#include <GL/glew.h>
#include "Mesh.hpp"

#include <cstring>
#include <stdio.h>

Mesh::Mesh() { /* Does nothing, it is okay to create empty meshes for anything */ }

Mesh::~Mesh()
{
    delete [] _vertices;
    delete [] _elements;
    delete [] _texcoords;

    delete [] _normals;

    // TODO: Get rid of buffers too, how?
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_nbo);
    glDeleteBuffers(1, &_ebo);

    glDeleteVertexArrays(1, &_vao);
}

void Mesh::Bind()
{
    glBindVertexArray(_vao);
}

void Mesh::LoadToGL(GLuint shader)
{
    if(_vertices == nullptr || _elements == nullptr)
    {
        printf("Vertices and/or elements not set, can not load to GL");
        return;
    }

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    GLenum GLDrawMode = GL_STATIC_DRAW;

    // Vertices
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER,  _vertexFloatArrayLength * sizeof(float), _vertices, GLDrawMode);

    GLint positionAttribute = glGetAttribLocation(shader, "position");
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(positionAttribute);

    // Elements
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementCount * sizeof(int), _elements, GLDrawMode);

    // Only do if we have normals
    if (_normals != nullptr)
    {
        glGenBuffers(1, &_nbo);
        glBindBuffer(GL_ARRAY_BUFFER, _nbo);
        glBufferData(GL_ARRAY_BUFFER, _vertexFloatArrayLength * sizeof(GLfloat), _normals, GLDrawMode);

        GLint normalAttribute = glGetAttribLocation(shader, "normal");
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(normalAttribute);
    }

    if (_texcoords != nullptr)
    {
        glGenBuffers(1, &_tbo);
        glBindBuffer(GL_ARRAY_BUFFER, _tbo);
        glBufferData(GL_ARRAY_BUFFER, _texcoordFloatArrayLength * sizeof(GLfloat), _texcoords, GLDrawMode);

        GLint texcoordAttribute = glGetAttribLocation(shader, "texcoord");
        glVertexAttribPointer(texcoordAttribute, 2, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(texcoordAttribute);
    }
}

void Mesh::SetVertices(GLfloat * verticesAsFloats, int vertexCountAsVector3)
{
    delete [] _vertices;

    _vertexCount = vertexCountAsVector3;
    _vertexFloatArrayLength = 3 * _vertexCount;
    _vertices = new float[_vertexFloatArrayLength];

    std::memcpy(_vertices, verticesAsFloats, _vertexFloatArrayLength * sizeof(float));
}

void Mesh::SetNormals(GLfloat * normals, int normalsCountAsVector3 )
{
    if (normalsCountAsVector3 != _vertexCount)
    {
        printf ("Normal count does not match vertex count!\n");
        return;
    }

    delete [] _normals;
    _normals = new float [_vertexFloatArrayLength];
    std::memcpy(_normals, normals, _vertexFloatArrayLength * sizeof(float));
}

void Mesh::SetElements(GLuint * elements, int elementCount)
{
    delete [] _elements;

    _elementCount = elementCount;
    _elements = new GLuint[_elementCount];

    std::memcpy(_elements, elements, _elementCount * sizeof(float));
}


void Mesh::SetTexcoords(GLfloat *texcoordsAsFloats, int texcoordCountAsVector2)
{
    if (texcoordCountAsVector2 != _vertexCount)
    {
        printf("Texcoord count does not match vertex count");
        return;
    }

    delete [] _texcoords;
    _texcoordFloatArrayLength = 2 * _vertexCount;
    _texcoords = new float [_texcoordFloatArrayLength];
    std::memcpy(_texcoords, texcoordsAsFloats, _texcoordFloatArrayLength * sizeof(GLfloat));
}

