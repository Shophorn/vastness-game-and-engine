/*
Leo Tamminen
22/11/2018.
*/


#include <fstream>
#include <string>
#include <sstream>

#include <SOIL.h>

#include "Loader.hpp"
#include "FileOperations.hpp"
#include "StringOperations.hpp"
#include "DEBUG.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

bool loader::LoadTextureRGB(const char *path, GLuint *target)
{
    GLuint texture;
    glGenTextures (1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);



    int width, height;
    unsigned char * image =
            SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

    // Flip around since SOIL loads images the other way, and we don't want to mess shaders because of this
    int byte_count = width * height * 3;
    for (int i = 0; i < byte_count / 2; i +=3)
    {
        int pixel_x = i % (width * 3);
        int pixel_y = i / (width * 3);
        int p = (height - 1 - pixel_y) * width * 3 + pixel_x;

        unsigned char r = image [i];
        image [i] = image[p];
        image[p] = r;

        unsigned char g = image [i + 1];
        image [i + 1] = image[p + 1];
        image [p + 1] = g;


        unsigned char b = image [i + 2];
        image [i + 2] = image [p + 2];
        image [p + 2] = b;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);



    *target = texture;
    return true;

}

bool loader::LoadTextureRGBA(const char *path, GLuint *target)
{
    GLuint texture;
    glGenTextures (1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height;
    unsigned char * image =
            SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

    // Flip around since SOIL loads images the other way, and we don't want to mess shaders because of this
    int byte_count = width * height * 4;
    for (int i = 0; i < byte_count / 2; i +=4)
    {
        int pixel_x = i % (width * 4);
        int pixel_y = i / (width * 4);
        int p = (height - 1 - pixel_y) * width * 4 + pixel_x;

        unsigned char r = image [i];
        image [i] = image[p];
        image[p] = r;

        unsigned char g = image [i + 1];
        image [i + 1] = image[p + 1];
        image [p + 1] = g;


        unsigned char b = image [i + 2];
        image [i + 2] = image [p + 2];
        image [p + 2] = b;

        unsigned char a = image [i + 3];
        image [i + 3] = image[p + 3];
        image [p + 3] = a;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    *target = texture;
    return true;

}


///////////////////////////////////
// MESHES                        //
//////////////////////////////////

MeshAsset * convertFromOBJ(std::ifstream && file)
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

    return asset;

} // objConvert


template <> MeshAsset loader::load<MeshAsset>(const std::string & path)
{
    if (strOps::compareExtension(path, "obj"))
    {
        return *convertFromOBJ(std::ifstream(path));
    }
    assert(false && "only .objs supported now");

    return MeshAsset{};
}