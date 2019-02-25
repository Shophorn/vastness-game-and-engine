/*
Leo Tamminen
22/11/2018.
*/


#include <fstream>
#include <string>

#include <SOIL.h>

#include "Loader.hpp"
#include "FileOperations.hpp"
#include "StringOperations.hpp"
#include "DEBUG.hpp"
#include "Mesh.hpp"

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

template <> MeshAsset loader::load<MeshAsset>(const std::string & path)
{
    if (strOps::compareExtension(path, "obj"))
    {
        return *convert::fromOBJ(std::ifstream(path));
    }
    assert(false && "only .objs supported now");

    return MeshAsset{};
}