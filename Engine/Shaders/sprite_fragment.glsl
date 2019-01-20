/*
Sprite Fragment

Unlit shader, that clips at alpha 0.5
*/
#version 150

in vec3 Normal;
in vec2 Texcoord;
in vec3 WorldPosition;

uniform vec3 lightDir;
uniform vec3 cameraPos;
uniform sampler2D mainTexture;

out vec4 outColor;

uniform float smoothness = 0.65f;

void main ()
{
    vec4 tex = texture(mainTexture, Texcoord);
    vec3 n  = normalize(Normal);

    vec3 diffuse = tex.rgb;

    outColor = vec4 (diffuse, 1.0);
}