// Vertex
#version 150

in vec3 position;
in vec3 normal;
in vec2 texcoord;

uniform mat4 model = mat4 (1.0);
uniform mat4 model_it = mat4 (1.0);

uniform mat4 projection = mat4(1.0);
uniform mat4 view = mat4(1.0);

out vec3 Normal;
out vec2 Texcoord;
out vec3 WorldPosition;

void main()
{
    gl_Position = projection * view * model * vec4 (position, 1.0);
    Normal = mat3(model_it) * normal;
    Texcoord = texcoord;
    WorldPosition = (model * vec4(position, 1.0)).xyz;
}
