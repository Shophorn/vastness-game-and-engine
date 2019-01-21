/*
Sprite Fragment

Unlit shader, that clips at alpha _AlphaClip
*/
#version 150

in vec3 Normal;
in vec2 Texcoord;
in vec3 WorldPosition;

uniform vec3 lightDir;
uniform vec3 cameraPos;
uniform sampler2D mainTexture;

out vec4 outColor;

uniform float _AlphaClip = 0.5f;

void main ()
{
    vec4 tex = texture(mainTexture, Texcoord);
    if (tex.a < _AlphaClip)
    {
        discard;
    }
    outColor = vec4 (tex.rgb, 1.0);
}