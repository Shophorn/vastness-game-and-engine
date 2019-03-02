/*
LeoTamminen
Created 26/02/2019
*/

#include <SOIL.h>
#include <string>
#include <cassert>
#include "Textures.hpp"
#include "../Loader.hpp"

void Textures::addLoadInfo(const serialization::Value &loadInfoValues)
{
    auto jsonTextureArray = loadInfoValues.GetArray();
    for (const auto & item : jsonTextureArray)
    {
        auto obj = item.GetObject();
        auto name = obj["name"].GetString();
        textureLoadInfo info;
        info.path = obj["path"].GetString();

        std::string colorModeStr = obj["color mode"].GetString();
        if (colorModeStr == "RGBA")
            info.colorMode = textureLoadInfo::RGBA;
        else if (colorModeStr == "RGB")
            info.colorMode = textureLoadInfo::RGB;

        _nameInfoMap.emplace(name, textureInfo{ 0, info });
    }
}


/////////////////////////
// LOADING             //
/////////////////////////
GLuint LoadTextureRGBA(textureLoadInfo loadInfo)
{
    GLuint texture;
    glGenTextures (1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height;
    unsigned char * image =
            SOIL_load_image(loadInfo.path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

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

    return texture;
}

textureHandle Textures::getHandle(std::string name)
{
    assert(_nameInfoMap.find(name) != _nameInfoMap.end() && "name not found");


    auto * info = &_nameInfoMap[name];
    if (info->handle == 0)
    {
        info->handle = LoadTextureRGBA(info->loadInfo);
    }
    return info->handle;
}