/*
Shophorn Games
Leo Tamminen
Created 28/01/2019
*/

#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "AssetLoader.hpp"

namespace Core
{
    struct SerializableAnimation
    {
        const char * name;
        int frameCount;
    };

    struct SerializebleAnimationAtlas
    {
        const char * texturePath;
        int rows;
        int columns;
        float frameRate;

        std::vector<SerializableAnimation> animations;
    };


    class SpriteAnimator
    {
    public:
        GLuint texture;
        GLuint shaderId;

        GLint frameLocation;
        GLint animationIndexLocation;

       std::vector<int> frameCounts;

        int currentAnimation;
        int currentFrame;
        float frameRate;


        float time = 0;

            SpriteAnimator(GLuint shaderId, SerializebleAnimationAtlas atlas)
        {
            this->shaderId = shaderId;

            texture = -1;
            AssetLoader::LoadTextureRGBA(atlas.texturePath, &texture);

            int animationCount = atlas.animations.size();
            frameCounts = std::vector<int>(animationCount);
            for (int i = 0; i < animationCount; i++)
            {
                frameCounts[i] = atlas.animations[i].frameCount;
            }


            // Set frame sizes as fractions of [0...1] range per atlas sizes
            glUniform1f(glGetUniformLocation(shaderId, "frameWidth"), 1.0f / atlas.columns);
            glUniform1f(glGetUniformLocation(shaderId, "frameHeight"), 1.0f / atlas.rows);

            frameLocation = glGetUniformLocation(shaderId, "currentFrame");
            animationIndexLocation = glGetUniformLocation(shaderId, "currentAnimation");

            currentAnimation = 0;
            currentFrame = 0;
            frameRate = atlas.frameRate;
        }

        void SetAnimation(int index)
        {
            currentAnimation = index;
            // TODO: time should be reset with bigger animations so that they don't switch to between
            //time = 0;
        }

        void Update(float deltaTime)
        {
            time += deltaTime;
            currentFrame = int (time * frameRate) % frameCounts[currentAnimation];
        }

        void SetShaderValues()
        {
            glUseProgram(shaderId);
            glUniform1i(frameLocation, currentFrame);
            glUniform1i(animationIndexLocation, currentAnimation);
        }
    };
}