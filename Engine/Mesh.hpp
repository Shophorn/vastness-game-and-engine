#pragma once

#include <GL/glew.h>

class Mesh
{
private:
    GLfloat * _vertices = nullptr;
    GLfloat * _normals = nullptr;
    GLfloat * _texcoords = nullptr;

    // Length of vertices / 3
    int _vertexCount = 0;
    int _vertexFloatArrayLength = 0;
    int _texcoordFloatArrayLength = 0;

    GLuint * _elements = nullptr;
    // Actual number of elements aka triangleindices in _elements
    int _elementCount = 0;

    GLuint _vao = -1;
    GLuint _vbo  = -1;
    GLuint _ebo = -1;
    GLuint _nbo = -1;
    GLuint _tbo = -1;

public:
    Mesh ();
    ~Mesh();

    GLuint vao () const { return _vao; }

    int vertexCount() const { return _vertexCount; }
    int elementCount () const { return _elementCount; }

    void SetVertices(GLfloat *verticesAsFloats, int vertexCountAsVector3);
    void SetElements(GLuint * elements, int elementCount);
    void SetNormals(GLfloat *normalsAsFloats, int normalCountAsVector3);
    void SetTexcoords(GLfloat * texcoordsAsFloats, int texcoordCountAsVector2);

    void LoadToGL(GLuint shader);

    void Bind();
};

