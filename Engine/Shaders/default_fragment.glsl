// Fragment
#version 150

in vec3 Normal;
in vec2 Texcoord;
in vec3 WorldPosition;

uniform vec3 lightDir;
uniform vec3 cameraPos;
uniform sampler2D mainTexture;
uniform vec3 _LightColor;

out vec4 outColor;

uniform float smoothness = 0.65f;

void main ()
{
    vec4 tex = texture(mainTexture, Texcoord);
    vec3 n  = normalize(Normal);

    float NdotL = max(0, dot(n, lightDir));
    vec3 diffuse = tex.rgb * NdotL * _LightColor;

    vec3 viewDir = normalize(cameraPos - WorldPosition);
    vec3 halfVector = normalize(viewDir + lightDir);

    float specularValue = pow(max(0, dot(halfVector, n)), 100 * smoothness);
    vec3 specular = specularValue * tex.a * _LightColor;

    outColor = vec4 (diffuse + specular, 1.0);
}