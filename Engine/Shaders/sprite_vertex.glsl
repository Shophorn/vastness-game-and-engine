// Vertex
#version 150

in vec3 position;
in vec3 normal;
in vec2 texcoord;

uniform mat4 model;
uniform mat3 model_it;

uniform mat4 projection;
uniform mat4 view;
uniform float _Time;

out vec3 Normal;
out vec2 Texcoord;
out vec3 WorldPosition;

uniform float frameWidth = 1.0;
uniform float frameHeight = 1.0;

uniform int currentFrame = 0;
uniform int currentAnimation = 0;

uniform bool flipped;
uniform bool isAnimated;

float fmod(float value, float limit)
{
    return fract (value / limit) * limit;
}

void main()
{
    if (isAnimated)
    {
        // Animate from sprite atlas. Frames y starts from top, but uv.y starts form bottom.
        float x = (currentFrame + texcoord.x) * frameWidth;
        float y = 1 - (currentAnimation + 1 - texcoord.y) * frameHeight;

        Texcoord = vec2 (x, y);
    }
    else
    {
        Texcoord = texcoord;
    }

    gl_Position = projection * view * model * vec4 (position, 1.0);
    Normal = model_it * normal;
    WorldPosition = (model * vec4(position, 1.0)).xyz;
}
