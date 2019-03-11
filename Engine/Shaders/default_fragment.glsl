// Fragment
#version 150

in vec3 Normal;
in vec2 Texcoord;
in vec3 WorldPosition;

uniform vec3 lightDir = normalize(vec3(1, 2 ,5));
uniform vec3 cameraPos;
uniform sampler2D mainTexture;

uniform sampler2D _AlbedoTexture;
uniform sampler2D _NormalTexture;

uniform vec3 _LightColor = vec3(0.98, 0.97,0.87);
uniform vec3 _Ambient = vec3(0.1, 0.1, 0.1);

out vec4 outColor;

uniform float smoothness = 0.65f;

vec3 unpackNormals()
{
    vec3 normal = texture(_NormalTexture, Texcoord).xyz;
    normal = normal * 2 - 1;
    normal = normalize(normal + Normal);
    return normal;
}

void main ()
{
    // vec4 tex = texture(_AlbedoTexture, Texcoord);
    vec4 tex = texture(_AlbedoTexture, vec2(0.5,0.5));
    vec3 n  = unpackNormals();//normalize(Normal);

    float NdotL = max(0, dot(n, lightDir));
    vec3 diffuse = tex.rgb * NdotL * _LightColor;

    vec3 viewDir = normalize(cameraPos - WorldPosition);
    vec3 halfVector = normalize(viewDir + lightDir);

    float specularValue = pow(max(0, dot(halfVector, n)), 100 * smoothness);
    vec3 specular = specularValue * tex.a * _LightColor;

    // Use occlusion texture of course
    vec3 ambient = _Ambient * tex.rgb;

    outColor = vec4 (ambient + diffuse + specular, 1.0);
}