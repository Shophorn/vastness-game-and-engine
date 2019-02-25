#include <fstream>
#include <sstream>
#include <cassert>

#include "Assets.hpp"
#include "Mesh.hpp"
#include "Stopwatch.hpp"
#include "DEBUG.hpp"

namespace detail
{
    template<typename T>
    void generateBuffer(GLenum bufferType, GLuint *target, const std::vector<T> &data)
    {
        glGenBuffers(1, target);
        glBindBuffer(bufferType, *target);
        glBufferData(bufferType, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    }
}

template<>
MeshInstance instantiate(MeshAsset asset)
{
    assert(!asset.vertices.empty() && !asset.elements.empty() && "invalid mesh");

    MeshInstance instance{};
    glGenVertexArrays(1, &instance.vao);
    glBindVertexArray(instance.vao);

    GLenum GLDrawMode = GL_STATIC_DRAW;

    detail::generateBuffer(GL_ARRAY_BUFFER, &instance.verticesBO, asset.vertices);
    detail::generateBuffer(GL_ELEMENT_ARRAY_BUFFER, &instance.elementsBO, asset.elements);

    if (!asset.texcoords.empty())
        detail::generateBuffer(GL_ARRAY_BUFFER, &instance.texcoordBO, asset.texcoords);

    if (!asset.normals.empty())
        detail::generateBuffer(GL_ARRAY_BUFFER, &instance.normalsBO, asset.normals);

    instance.elementCount = static_cast<GLsizei>(asset.elements.size());

    return instance;
}

namespace detail
{
    void setAttribPointer(GLuint target, GLint size, GLuint shader, std::string name)
    {
        glBindBuffer(GL_ARRAY_BUFFER, target);
        auto location = glGetAttribLocation(shader, name.c_str());
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
    }

}
void setVertexAttributes(MeshInstance instance, Shader shader)
{
    glBindVertexArray(instance.vao);

    using namespace detail;
    setAttribPointer(instance.verticesBO, 3, shader.id, "position");

    if (instance.texcoordBO > 0 )
        setAttribPointer(instance.texcoordBO, 2, shader.id, "texcoord");

    if (instance.normalsBO > 0 )
        setAttribPointer(instance.normalsBO, 3, shader.id, "normal");

}


MeshAsset * convert::fromOBJ(std::ifstream && file)
{
    assert(file.good() && "Do not use bad files");

    // v's to the list
    // vt's to the list
    // vn's to the list
    // f's to the list of 3(iv/ivt/ivn)
    //	if f has more than 3 indices, split sequentically (1,2,3; 2,3,4...) and add to flist


    // find unique combinations from flist
    // create new float array according per unique combinations

    using namespace std;

    auto sw = Stopwatch::startNew();
    // Face (triangle, element) configuration
    vector<int> obj_faces;
    bool objContainsOnlyPositions = true;

    // Vertex positions, uvs and normals
    vector<float> obj_positions;
    vector<float> obj_texcoord;
    vector<float> obj_normals;

    int
        commentCount = 0,
        vertexCount = 0,
        uvCount = 0,
        normalCount = 0,
        faceCount = 0;

    // for debugging only
    int
        triangleCount = 0,
        quadCount = 0,
        ngonCount = 0;

    string id, lineStr;

    while(file >> id)
    {
        getline(file, lineStr);
        stringstream line (lineStr);

        if (id == "v")
        {
            float x, y, z;
            line >> x >> y >> z;
            obj_positions.push_back(x);
            obj_positions.push_back(y);
            obj_positions.push_back(z);

            vertexCount++;
        } // positions

        else if (id == "vt")
        {
            float u, v;
            line >> u >> v;
            obj_texcoord.push_back(u);
            obj_texcoord.push_back(v);

            uvCount++;
        } // texcoord

        else if (id == "vn")
        {
            float x, y, z;
            line >> x >> y >> z;
            obj_normals.push_back(x);
            obj_normals.push_back(y);
            obj_normals.push_back(z);

            normalCount++;
        } // normals

        else if (id == "f")
        {
            // if this is first encountered face, check whether or not file has normals and texcoords written
            if (obj_faces.empty())
            {
                for (char c : lineStr)
                {
                    if (c == '/')
                    {
                        objContainsOnlyPositions = false;
                        break;
                    }
                }
            }

            // extra whitespace after id but before first item
            line.ignore();

            if (objContainsOnlyPositions)
            {
                vector<int> face;

                string token;
                while (getline(line, token, ' '))
                {
                    face.push_back(stoi(token) - 1);
                }

                // deformed face
                if (face.size() < 3) continue;

                if (face.size() == 3)
                {
                    obj_faces.insert(obj_faces.end(), face.begin(), face.end());
                    triangleCount++;
                }
                else if (face.size() == 4)
                {
                    // We have [A, B, C, D], add [A, B, C], [C, D, A]
                    // May work sometimes, no quarantees though. Should do geometric computations.
                    int indices[] = {0, 1, 2, 2, 3, 0};
                    for (int i = 0; i < 6; i++)
                    {
                        // this happens 6 times
                        obj_faces.push_back(face[indices[i]]);
                    }

                    quadCount++;
                }
            }
            else
            {
                // initial container, where there can be more than three vertices
                vector<int> face;
                int faceVertexCount = 0;

                // Read indices to vector. Obj indexing starts from 1, so subtract 1
                string token;
                while (getline(line, token, '/'))
                {
                    // Position
                    face.push_back(token.empty() ? -1 : stoi(token) - 1);

                    // UV
                    getline(line, token, '/');
                    face.push_back(token.empty() ? -1 : stoi(token) - 1);

                    // Normal
                    getline(line, token, ' ');
                    face.push_back(token.empty() ? -1 : stoi(token) - 1);

                    faceVertexCount++;
                }

                // Deformed face
                if (faceVertexCount < 3) continue;

                if (faceVertexCount == 3)
                {
                    obj_faces.insert(obj_faces.end(), face.begin(), face.end());
                    triangleCount++;
                } else if (faceVertexCount == 4)
                {
                    // We have [A, B, C, D], add [A, B, C], [C, D, A]
                    // May work sometimes, no quarantees though. Should do geometric computations.
                    int indices[] = {0, 3, 6, 6, 9, 0}; // [0, 1, 2, 2, 3, 0] * 3
                    for (int i = 0; i < 6; i++)
                    {
                        // this happens 6 times, total of 18 push_backs
                        obj_faces.push_back(face[indices[i]]);
                        obj_faces.push_back(face[indices[i] + 1]);
                        obj_faces.push_back(face[indices[i] + 2]);
                    }

                    quadCount++;
                } else
                {
                    ngonCount++;

                    // As there might be more than 3 vertices on line, just naively split them
                    // to triangles, eg [0, 1, 2, 3, 4] --> [0, 1, 2], [1, 2, 3], [2, 3, 4]
                    // NEVER DO THIS KIND OF COMMENT
                    // -2 for things, another -1 for usual [length -1]
                    for (int i = 0; i < faceVertexCount - 3; i++)
                    {
                        int index = i * 3;
                        obj_faces.push_back(face[index]);
                        obj_faces.push_back(face[index + 1]);
                        obj_faces.push_back(face[index + 2]);

                        index = ((i + 1) % faceVertexCount) * 3;
                        obj_faces.push_back(face[index]);
                        obj_faces.push_back(face[index + 1]);
                        obj_faces.push_back(face[index + 2]);

                        index = ((i + 2) % faceVertexCount) * 3;
                        obj_faces.push_back(face[index]);
                        obj_faces.push_back(face[index + 1]);
                        obj_faces.push_back(face[index + 2]);
                    }
                }
            } // objContainsOnlyFaces
            faceCount++;
        }
    } // faces


    bool hasPositions = !obj_positions.empty();
    if (!hasPositions) return nullptr;

    bool hasTexcoords = !objContainsOnlyPositions && !obj_texcoord.empty();
    bool hasNormals = !objContainsOnlyPositions && !obj_normals.empty();

    int uniqueVertexCount = 0;
    vector<int> uniquePositions;
    vector<int> uniqueTexcoords;
    vector<int> uniqueNormals;

    // NOTE: remember dividing by three, since in each element there are three numbers (obj format: pos/tex/norm)
    int glElementSize = objContainsOnlyPositions ? obj_faces.size() : obj_faces.size() / 3;
    vector<unsigned> glElementsVector;
    glElementsVector.reserve(glElementSize);

    if (objContainsOnlyPositions)
    {
        for (int i = 0; i <obj_faces.size(); i++)
        {
            int pos = obj_faces[i];
            bool isUnique = true;
            GLuint lastIndex;
            for (int ii = 0; ii < uniqueVertexCount; ii++)
            {
                int uPos = uniquePositions[ii];

                lastIndex = ii;

                if (pos == uPos)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
            {
                uniqueVertexCount++;
                uniquePositions.push_back(pos);
                glElementsVector.emplace_back(uniqueVertexCount -1);
            }
            else
            {
                glElementsVector.emplace_back(lastIndex);
            }
        }
    }
    else
    {
        // go in steps of three (obj format: pos/tex/norm)
        for (int i = 0; i < obj_faces.size(); i += 3)
        {
            // Slice to separate pieces of data
            int pos = obj_faces[i];
            int tex = obj_faces[i + 1];
            int norm = obj_faces[i + 2];

            // is (pos/tex/norm) combination unique
            bool isUnique = true;
            GLuint lastIndex;
            for (int ii = 0; ii < uniqueVertexCount; ii++)
            {
                int uPos = uniquePositions[ii];
                int uTex = uniqueTexcoords[ii];
                int uNorm = uniqueNormals[ii];

                lastIndex = ii;

                if (pos == uPos && tex == uTex && norm == uNorm)
                {
                    isUnique = false;
                    break;
                }
            }

            if (isUnique)
            {
                uniqueVertexCount++;

                uniquePositions.push_back(pos);
                uniqueTexcoords.push_back(tex);
                uniqueNormals.push_back(norm);

                glElementsVector.emplace_back(uniquePositions.size() - 1);
            } else { // if (unique == false)
                glElementsVector.emplace_back(lastIndex);
            }
        }
    }

    // Unpack indices and vertices
    auto * asset = new MeshAsset();
    asset->elements = glElementsVector;

    asset->vertices.reserve(uniqueVertexCount * 3);
    asset->texcoords.reserve(uniqueVertexCount * 2);
    asset->normals.reserve(uniqueVertexCount * 3);

    auto * glPositionsVector = &asset->vertices;
    auto * glTexcoordsVector = &asset->texcoords;
    auto * glNormalsVector = &asset->normals;

    for (int i = 0; i < uniqueVertexCount; i++) {
        int op = uniquePositions[i] * 3;
        glPositionsVector->insert(glPositionsVector->end(), &obj_positions[op], &obj_positions[op + 3]);
    }

    if (hasTexcoords) {
        for (int i = 0; i < uniqueVertexCount; i++)
        {
            int ot = uniqueTexcoords[i] * 2;
            glTexcoordsVector->insert(glTexcoordsVector->end(), &obj_texcoord[ot], &obj_texcoord[ot + 2]);
        }
    }

    if (hasNormals) {
        for (int i = 0; i < uniqueVertexCount; i++)
        {
            int on = uniqueNormals[i] * 3;
            glNormalsVector->insert(glNormalsVector->end(), &obj_normals[on], &obj_normals[on + 3]);
        }
    }

    debug << "Loading obj took " << sw.seconds() << " s\n";
    return asset;

} // objConvert

